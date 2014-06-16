/******************************************************************************/
#include "GlobalOption.h"
#include "Define.h"
#include "OperationManager.h"
#include "CoreManager.h"
#include "GameFileDefine.h"
/******************************************************************************/


namespace EffectEditor {

	//-----------------------------------------------------------------------
	OperationManager::OperationManager()
		: mCameraSpeed(1000.0f)
	{

	}
	//-----------------------------------------------------------------------
	OperationManager::~OperationManager()
	{

	}

	//-----------------------------------------------------------------------
	void OperationManager::update( Dbl delta )
	{
		updateCameraOp( delta );
	}

	void OperationManager::revertCamera()
	{
		IScene* scene       = CoreManager::getInstance().getScene();
		if ( scene == NULL )
			return;

		ICamera* camera = scene->getActiveCamera();

		if ( camera )
		{
			camera->setPosition(Vec3(0, 2, -8));
			camera->getSceneNode()->setDirection(Vec3(0, 0, 1));
			WindowSet::main_win->updateCameraPos(0, 2, -8);
		}
	}

	void OperationManager::updateCameraOp( Dbl delta )
	{
		IInput* input       = CoreManager::getInstance().getEngineMain()->input();
		if ( input == NULL )
			return;

		if (!input->isFocusLastFrame())
			return;

		IScene* scene       = CoreManager::getInstance().getScene();
		if ( scene == NULL )
			return;

		ICamera* camera = scene->getActiveCamera();

		if ( camera )
		{
			Flt d = (Flt)delta * mCameraSpeed;

			//通过滚轮改变摄像机离地面距离
			Int	wheelRel = 0;
			if ( input->isMouseHolded(MB_Left) == false )
				wheelRel = input->getMouseWheel();

			if(wheelRel != 0)
			{
				Flt scale = 0.05f;
				Flt final_wheel = (Flt)-wheelRel * scale;

				Vec3 camera_pos;
				camera->getPosition(camera_pos);

				if ( abs(camera_pos.y)  > 1000.0f )
					final_wheel = (Flt)-wheelRel*1.0f;
				else if ( abs(camera_pos.y)  > 100.0f )
					final_wheel = (Flt)-wheelRel*0.1f;
				else if ( abs(camera_pos.y)  > 0.0f )
					final_wheel = (Flt)-wheelRel*0.01f;

				camera->translate(Vec3(0, 0, final_wheel));
			}

			//控制角度
			if( input->isMouseHolded(MB_Right) )
			{
				Vec2 rel = input->getMouseMoveDelta();
				camera->pitch( rel.y * (-3.0f) );
				camera->yaw( rel.x * (-3.0f) );
			}

			//if ( input->isAltOn() )
			{
				bool camera_translate = false;
				Vec3 vec_trans;
				Flt  scale = 0.005f;

				if ( input->isKeyHolded(KC_A) )
				{
					vec_trans = Vec3(-d,0,0);
					camera_translate = true;
				}
				else if ( input->isKeyHolded(KC_D) )
				{
					vec_trans = Vec3(d,0,0);
					camera_translate = true;
				}
				else if ( input->isKeyHolded(KC_W) )
				{
					vec_trans = Vec3(0,0,-d);
					camera_translate = true;
				}
				else if ( input->isKeyHolded(KC_S) )
				{
					vec_trans = Vec3(0,0,d);
					camera_translate = true;
				}

				if ( camera_translate )
				{
					Vec3 camera_pos;
					camera->getPosition(camera_pos);

					vec_trans.x *= scale;
					vec_trans.y *= scale;
					vec_trans.z *= scale;

					camera->translate(vec_trans);
				}
			}

			Vec3 camera_pos;
			camera->getPosition(camera_pos);
			WindowSet::main_win->updateCameraPos(camera_pos.x, camera_pos.y, camera_pos.z);
		}
	}

	void OperationManager::addEntity(U32 id)
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if (!scene)
			return;

		IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
		if (!component)
			return;

		IEntity* entity = NULL;
		if (WindowSet::main_win->getCurrentTabIndex() != 0)
		{
			entity = component->createModelEffect(id);
			if (!entity)
				return;

			entity->getSceneNode()->setVisible(false);

			IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
			if (!component)
				return;

			IEffectXmlSerializer* effectXmlSer = component->getEffectXmlSerializer();

			if (effectXmlSer)
				effectXmlSer->addEffectObjectFormat(entity, true);

			WindowSet::main_win->addEntitytoList(component->getModelName(entity));
		}
		else
		{
			entity = component->createSlotModelEffect(id);
			WindowSet::main_win->addEntitytoList(entity->getName().c_str());
		}

		
	}

	void OperationManager::addEffect(Str8 templatename)
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if (!scene)
			return;

		IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
		if (!component)
			return;

		IPUEffect* effect = component->createPUEffect(templatename.c_str());
		if (!effect)
			return;

		effect->getSceneNode()->setVisible(false);
		effect->getSceneNode()->setPosition(Vec3(0, 0, 0));

		IEffectXmlSerializer* effectXmlSer = component->getEffectXmlSerializer();
		if (effectXmlSer)
			effectXmlSer->addEffectObjectFormat(effect, true);

		WindowSet::main_win->addEffecttoList(component->getEffectName(effect));
	}

	void OperationManager::addEvent(const std::string name, float eventTiming)
	{
		IScene* scene = CoreManager::getInstance().getScene();
		if (!scene)
			return;

		IEffectComponent* component = CoreManager::getInstance().getCurEffectComponent();
		if (!component)
			return;

		IEffectEvent* event = component->createEffectEvent(name, eventTiming);

		IEffectXmlSerializer* effectXmlSer = component->getEffectXmlSerializer();
		if (effectXmlSer)
			effectXmlSer->addEffectObjectFormat(event, true);

		WindowSet::main_win->addEventName(event->getName(), event->getEventName());
	}

	bool OperationManager::loadEffectComponentFile(const Str filename, Str componentName)
	{
		// 初始化场景
		CoreManager::getInstance().initScene(componentName);

		IScene* scene = CoreManager::getInstance().getScene();
		if (!scene)
			return false;

		IEffectComponent* effectComponent = CoreManager::getInstance().getCurEffectComponent();
		if (!effectComponent)
			return false;

		IEffectXmlSerializer* xmlserializer = effectComponent->getEffectXmlSerializer();
		if (!xmlserializer)
			return false;

		return xmlserializer->loadEffectComponentFormat(filename.c_str());
	}

	bool OperationManager::newEffectComponentFile()
	{
		// 初始化场景
		CoreManager::getInstance().initScene();

		IScene* scene = CoreManager::getInstance().getScene();
		if (!scene)
			return false;

		IEffectComponent* effectComponent = CoreManager::getInstance().getCurEffectComponent();
		if (!effectComponent)
			return false;

		IEffectXmlSerializer* xmlserializer = effectComponent->getEffectXmlSerializer();
		if (!xmlserializer)
			return false;

		return true;
	}
}