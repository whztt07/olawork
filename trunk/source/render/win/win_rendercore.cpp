#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "win_renderwindow.h"

#include "../ola_resourcemng.h"
#include "../ola_primitive.h"

#include "../ola_mesh.h"
#include "../ola_skin.h"

#include "win_impls.h"
#include "win_rendercore.h"

#include "../impls/ola_geometry_impl.h"

#include "../ola_device.h"

#define  lg(...) printf(__VA_ARGS__)

OlaRenderCore::OlaRenderCore():
mRender(0),
mSceneMng(0),
mCurrentWindow(0)
{
	
}

OlaRenderCore::~OlaRenderCore()
{
	release();
}

OlaRenderDevice* gDevice = 0;
OlaRenderDevice* GetRenderDevice()
{
	return gDevice;
}

bool OlaRenderCore::initialize(unsigned int hwnd)
{
	RECT rect;
	::GetWindowRect((HWND)hwnd,&rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	mDevice = SpawnGLRenderDevice();
	mDevice->init(hwnd);

	gDevice = mDevice;

	mRender = new OlaRender();
	mRender->onInitRender(w,h,mDevice);

	mSceneMng = new OlaRenderSceneMng(mRender);
	mSceneMng->initialize();

	mRender->setRenderScene(mSceneMng->scene());

	//mSceneMng->loadScene("level/beach001_simple.xml",mRender);
	//mSceneMng->loadModelFromDML("art/common/waitingroom001_teapoy001.dml",mRender);

	olaVec3 cam_pos(0,-5,0);	
	olaVec3 cam_tag(0,0,0);

	cam_pos.Set(-169.91f,322.12f,140.78f);	
	cam_tag.Set(-70.37f,217.91f,83.68f);

	cam_pos.Set(122.31f,82.37f,9.61f);		
	cam_tag.Set(73.37f,-61.42f,-21.68f);

	tViewParam vp;
	mRender->getViewFrustum(0)->toViewParam(&vp);

	vp.pos[0] = cam_pos.x;	vp.pos[1] = cam_pos.y;	vp.pos[2] = cam_pos.z;

	vp.lookat[0] = cam_tag.x;
	vp.lookat[1] = cam_tag.y;
	vp.lookat[2] = cam_tag.z;

	mRender->getViewFrustum(0)->fromViewParam(&vp);

    olaVec3 light0_lookatpt(0.0f,0.0f,0.0f);
	olaVec3 light0_position(200.0f,200.0f,200.0f);
	mRender->setDirLight(0,light0_position,light0_lookatpt);

	return true;
}

void OlaRenderCore::release()
{
	if (mRender)
	{
		mRender->onRelease();
		delete mRender;
		mRender = 0;
	}

	if(mSceneMng)
	{
		delete mSceneMng;
		mSceneMng = 0;
	}

	RenderWindowTable::iterator wi = mWindows.begin();
	while(wi != mWindows.end())
	{
		wi->second->release();
		delete wi->second;
		wi++;
	}
	mWindows.clear();

	if(mDevice)
	{
		delete mDevice;
		mDevice = 0;
	}
}

void OlaRenderCore::beginDraw()
{
	if(mCurrentWindow)
	{
		int w = mCurrentWindow->getWidth();
		int h = mCurrentWindow->getHeight();

		if( w != mRender->getScreenW() || h != mRender->getScreenH() )
		{
			mRender->onResize(w,h);
		}
	}
}

void OlaRenderCore::drawSceneActors()
{
	if(mRender)
	{
		//if(mSceneMng->draw_all)
		//{
		//	OlaRenderSceneMng::ModelList& model_list = mSceneMng->models();

		//	for (int i = 0 ; i != model_list.size() ; i++)
		//	{
		//		CModel* m = model_list[i];
		//		mRender->pushToRender(m);
		//	}
		//}
		
		mRender->onRender(0.0f);
	}
}

void OlaRenderCore::endDraw()
{
	if(mCurrentWindow)
	{
		mCurrentWindow->swapBuffer();
	}
}

void OlaRenderCore::getView(ola::tViewParam* vp)
{
	OlaVFrustum* vf = mRender->getViewFrustum(0);
	tViewParam t;
	vf->toViewParam(&t);
	memcpy(vp,&t,sizeof(tViewParam));
}

void OlaRenderCore::setView(ola::tViewParam* vp)
{
	OlaVFrustum* vf = mRender->getViewFrustum(0);
	tViewParam t;
	memcpy(&t,vp,sizeof(tViewParam));
	vf->fromViewParam(&t);	
}

void OlaRenderCore::setCamera(int index,ola::vec3& pos,ola::vec3& tag)
{
	olaVec3 _pos(pos.x,pos.y,pos.z);
	olaVec3 _tag(tag.x,tag.y,tag.z);

	mRender->setCamera(index,_pos,_tag);	
}

void OlaRenderCore::getCamera(int index,ola::vec3& pos,ola::vec3& tag)
{
	olaVec3 _pos,_tag;

	mRender->getCamera(index,_pos,_tag);

	memcpy(&pos,&_pos,sizeof(olaVec3));
	memcpy(&tag,&_tag,sizeof(olaVec3));
}

void OlaRenderCore::getViewMatrix(float* mat)
{
	olaMat4 vmat = mRender->getViewFrustum(0)->getViewMatrix();
	memcpy(mat,vmat.ToFloatPtr(),sizeof(olaMat4));
}

void OlaRenderCore::getProjMatrix(float* mat)
{
	olaMat4 vmat = mRender->getViewFrustum(0)->getProjMatrix();
	memcpy(mat,vmat.ToFloatPtr(),sizeof(olaMat4));
}

ola::IRenderWindow*	OlaRenderCore::createWindow(ola::RenderWindowInfo* info)
{
	int index = mWindows.size();
	OlaRenderWindow* w = new OlaRenderWindow(index,this);
	w->resizeRenderWindow(info);
	mWindows[index] = w;
	return w;
}

void OlaRenderCore::setWindow(ola::IRenderWindow* wnd)
{
	int index = wnd->getIndex();

	if(mCurrentWindow && index == mCurrentWindow->getIndex())
		return;

	RenderWindowTable::iterator wi = mWindows.find(index);
	if(wi != mWindows.end())
	{
		mCurrentWindow = wi->second;
		mCurrentWindow->setActive();
	}	
}

ola::IPrimitive* OlaRenderCore::createPrimitive(ola::PrimitiveType type)
{
	OlaPrimitive* prim = new OlaPrimitive(OlaPrimitiveParam::PRI_LINE);
	OlaMaterial* pri_mat = mRender->getResourceMng()->getPrimitiveMaterial();
	prim->renderop()->material(pri_mat);

	OlaPrimitiveImpl* impl = new OlaPrimitiveImpl(prim,mSceneMng);
	//mSceneMng->prims().push_back(prim);
	return impl;
}

ola::IStaticModel* OlaRenderCore::createStaticModel(const char* filename)
{
	CModel* model = mSceneMng->loadModelFromDML(filename);
	
	OlaStaticModelImpl* impl = new OlaStaticModelImpl(model,mRender->getResourceMng());
	return impl;
}

ola::IActor* OlaRenderCore::createActor( const char* chr_filename )
{	
	return 0;
}

void OlaRenderCore::pushRender(ola::IPrimitive* r)
{
	OlaPrimitiveImpl* impl = static_cast<OlaPrimitiveImpl*>(r);
	mRender->pushToRender(impl->mPrimitive);
}

void OlaRenderCore::pushRender(ola::IStaticModel* r)
{
	OlaStaticModelImpl* impl = static_cast<OlaStaticModelImpl*>(r);
	mRender->pushToRender(impl->mGeometry->mModel);
}

void OlaRenderCore::pushRender( ola::IRenderable* r )
{
	OlaRenderableImpl* impl = static_cast<OlaRenderableImpl*>(r);
	
	OlaRenderableImpl::RenderOpList& op_list = impl->mRenderOps;
	OlaRenderableImpl::RenderOpList::iterator op_i = op_list.begin();
	while(op_i != op_list.end())
	{
		OlaRenderOp* op = (*op_i);

		op->worldtrans.Identity();

		mRender->pushToRender(op);
		
		op_i++;
	}
}

void OlaRenderCore::pushRender( ola::IGeometry* g )
{
	OlaMeshGeometryImpl* impl = static_cast<OlaMeshGeometryImpl*>(g);

	OlaArray<OlaRenderOp*>& op_list = impl->renderOps();
	for (unsigned int i = 0 ; i < op_list.size() ; i++)
	{
		OlaRenderOp* op = op_list[i];
		mRender->pushToRender(op);
	}
}

int OlaRenderCore::loadActionResourceFromASE( const char* act_name,const char* ase_filename )
{
	return -1;
}

int OlaRenderCore::removeActionResource( const char* act_name )
{
	return -1;
}

int OlaRenderCore::loadBodyPartResourceFromBPT( const char* bpt_name,const char* bpt_filename )
{
	return -1;
}

int OlaRenderCore::removeBodyPartResource( const char* bpt_name )
{
	return -1;
}

int OlaRenderCore::loadSkeletonResourceFromASE( const char* name,const char* filename )
{
	return -1;
}

int OlaRenderCore::removeSkeletonResource( const char* name )
{
	return -1;
}

ola::ICharacter* OlaRenderCore::createCharacter( const char* chr_filename )
{
	OlaSkeletonModel* skel_model = mSceneMng->loadSkeletonModelFromCHR(chr_filename);

	OlaCharacterImpl* impl = new OlaCharacterImpl(skel_model);

	return impl;
}

ola::ILight* OlaRenderCore::createLight( const char* name )
{	
	OlaLight* l = new OlaLight();
	OlaLightImpl* impl = new OlaLightImpl(l);
	return impl;
}

void OlaRenderCore::clearResourceCache( const char* res_name )
{
	mRender->getResourceMng()->clearResourceCache(res_name);
}

int OlaRenderCore::getResourceNum( const char* res_name )
{
	return mRender->getResourceMng()->getResourceNum(res_name);
}

ola::IScene* OlaRenderCore::createScene( const char* name ,ola::IScene::SCENE_TYPE t)
{
	OlaRenderScene* scene = 0;
	switch(t)
	{
	case ola::IScene::SCENE_SMALL:
		scene = mSceneMng->createScene(name,OlaRenderSceneMng::SCENE_SMALL);
		break;
	case ola::IScene::SCENE_OUTDOOR:
		break;
	case ola::IScene::SCENE_INDOOR:
		break;
	}

	if(scene)
	{
		OlaSceneImpl* impl = new OlaSceneImpl(scene,mSceneMng);
		return impl;
	}
	else
		return 0;
}

void OlaRenderCore::setRenderingScene( ola::IScene* scene )
{
	OlaSceneImpl* impl = dynamic_cast<OlaSceneImpl*>(scene);
	mSceneMng->setRenderScene(impl->mScene);
	mRender->setRenderScene(mSceneMng->scene());
}
