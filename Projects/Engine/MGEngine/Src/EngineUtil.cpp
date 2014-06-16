/******************************************************************************/
#include "stdafx.h"
#include "EngineUtil.h"
#include "MGEngineUtility.h"
#include "ResourceManager.h"
#include "Entity.h"
/******************************************************************************/

namespace MG
{
	//-----------------------------------------------------------------------------------------------------
	Bool EngineUtil::isTextureExist( const Str& name, const Str& group )
	{
		Str groupName = group;

		if ( groupName.empty() )
			groupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		if ( Ogre::ResourceGroupManager::getSingleton().resourceGroupExists( groupName ) )
		{
			Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(name, groupName);
			return !texture.isNull();
		}

		return false;
	}
	//-----------------------------------------------------------------------------------------------------
	Bool EngineUtil::create2DTexture(const Str& name, const Str& group, U32 width, U32 height)
	{
		Str groupName = group;

		if ( groupName.empty() )
			groupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		if ( !Ogre::ResourceGroupManager::getSingleton().resourceGroupExists( groupName ) )
		{
			Ogre::ResourceGroupManager::getSingleton().createResourceGroup(group,false);
			Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(group);
		}
		else
		{
			Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(name, groupName);
			if ( !texture.isNull() )
				return false;
		}

		Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().createManual(name, groupName, TEX_TYPE_2D, 
			width, height, 0, PF_A8R8G8B8, TU_DYNAMIC /*TU_DYNAMIC_WRITE_ONLY_DISCARDABLE*/);

		return !texture.isNull();
	}
	//-----------------------------------------------------------------------------------------------------
	Bool EngineUtil::load2DTexture( const Str& name, const Str& path, const Str& group )
	{
		Str groupName = group;

		if ( groupName.empty() )
			groupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		MG::ResourceManager::getSingleton().loadResourceGroup( groupName, path );

		Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(name, groupName);
		if ( texture.isNull() )
		{
			texture = Ogre::TextureManager::getSingleton().load(name, groupName, TEX_TYPE_2D, 
				0, 1.0f, false, PF_A8R8G8B8 );
		}

		return !texture.isNull();
	}
	//-----------------------------------------------------------------------------------------------------
	void EngineUtil::unload2DTexture( const Str& name, const Str& group )
	{
		Str groupName = group;

		if ( groupName.empty() )
			groupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		if ( Ogre::ResourceGroupManager::getSingleton().resourceGroupExists( groupName ) )
		{
			Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(name, groupName);

			if ( !texture.isNull() )
			{
				Ogre::TextureManager::getSingleton().unload(texture.getPointer()->getHandle());
				Ogre::TextureManager::getSingleton().remove(texture.getPointer()->getHandle());
			}
		}
	}
	//-----------------------------------------------------------------------------------------------------
	const VecI2& EngineUtil::getTextureSize( const Str& name, const Str& group, Bool cache )
	{
		Str groupName = group;

		if ( groupName.empty() )
			groupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		// 获取一个TextureSize的
		static Str old_name;
		static Str old_group;
		static VecI2 old_size;

		if (old_name == name && old_group == groupName && cache)
			return old_size;
		old_name = name;
		old_size = VecI2(0,0);

		if ( name.empty() || groupName.empty() )
			return old_size;

		Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().getByName(name, groupName);

		if ( !texture.isNull() )
		{
			old_size.x = texture.getPointer()->getWidth();
			old_size.y = texture.getPointer()->getHeight();
		}

		return old_size;
	}
	//-----------------------------------------------------------------------------------------------------
	Bool EngineUtil::drawTextureToSurface(const Str& srcName, const Str& srcGroup, VecI2 srcLeftTop, VecI2 srcSize,  
		const Str& destName, const Str& destGroup, VecI2 destLeftTop, VecI2 destSize)
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////

		Str srcGroupName = srcGroup;
		Str destGroupName = destGroup;

		if ( srcGroupName.empty() )
			srcGroupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		if ( destGroupName.empty() )
			destGroupName = ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		
		Ogre::TexturePtr src_texture = Ogre::TextureManager::getSingleton().getByName(srcName, srcGroupName);
		if ( src_texture.isNull() )
			return false;

		HardwarePixelBufferSharedPtr src_buffer = src_texture->getBuffer(0,0);
		if ( src_buffer.isNull() )
			return false;

		Ogre::TexturePtr dest_texture = Ogre::TextureManager::getSingleton().getByName(destName, destGroupName);
		if ( dest_texture.isNull() )
			return false;

		HardwarePixelBufferSharedPtr dest_buffer = dest_texture->getBuffer(0,0);
		if ( dest_buffer.isNull() )
			return false;

		////////////////////////////////////////////////////////////////////////////////////////////////////

		//检查源拷贝图片的像素边界

		srcLeftTop.x = min( srcLeftTop.x, (I32)src_buffer.getPointer()->getWidth() );
		srcLeftTop.x = max( 0, srcLeftTop.x );

		srcLeftTop.y = min( srcLeftTop.y, (I32)src_buffer.getPointer()->getHeight() );
		srcLeftTop.y = max( 0, srcLeftTop.y );

		VecI2 srcRightButtom = srcLeftTop + srcSize;

		srcRightButtom.x = min( srcRightButtom.x, (I32)src_buffer.getPointer()->getWidth() );
		srcRightButtom.x = max( 0, srcRightButtom.x );

		srcRightButtom.y = min( srcRightButtom.y, (I32)src_buffer.getPointer()->getHeight() );
		srcRightButtom.y = max( 0, srcRightButtom.y );

		if ( srcLeftTop.x > srcRightButtom.x )
			srcLeftTop.x = srcRightButtom.x;

		if ( srcLeftTop.y > srcRightButtom.y )
			srcLeftTop.y = srcRightButtom.y;		

		////////////////////////////////////////////////////////////////////////////////////////////////////

		//检查目标拷贝图片的像素边界

		destLeftTop.x = min( destLeftTop.x, (I32)dest_buffer.getPointer()->getWidth() );
		destLeftTop.x = max( 0, destLeftTop.x );

		destLeftTop.y = min( destLeftTop.y, (I32)dest_buffer.getPointer()->getHeight() );
		destLeftTop.y = max( 0, destLeftTop.y );

		VecI2 destRightButtom = destLeftTop + destSize;

		destRightButtom.x = min( destRightButtom.x, (I32)dest_buffer.getPointer()->getWidth() );
		destRightButtom.x = max( 0, destRightButtom.x );

		destRightButtom.y = min( destRightButtom.y, (I32)dest_buffer.getPointer()->getHeight() );
		destRightButtom.y = max( 0, destRightButtom.y );

		if ( destLeftTop.x > destRightButtom.x )
			destLeftTop.x = destRightButtom.x;

		if ( destLeftTop.y > destRightButtom.y )
			destLeftTop.y = destRightButtom.y;		

		////////////////////////////////////////////////////////////////////////////////////////////////////

		Image::Box srcImageBox = Image::Box( srcLeftTop.x,srcLeftTop.y,srcRightButtom.x,srcRightButtom.y );
		Image::Box destImageBox = Image::Box( destLeftTop.x,destLeftTop.y, destRightButtom.x, destRightButtom.y );

		const PixelBox& srcPixelBox = src_buffer->lock(srcImageBox, HardwareBuffer::HBL_NORMAL);
		dest_buffer->blitFromMemory(srcPixelBox, destImageBox);
		src_buffer->unlock();

		return true;

		////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	//-----------------------------------------------------------------------------------------------------
	void EngineUtil::setTextureAnimation( IEntity* entity, Vec2 uv_start, Vec2 uv_speed )
	{

		Entity* _entity = dynamic_cast<Entity*>(entity);
		if ( _entity && _entity->getModelObject() )
		{
			Ogre::Entity* ogreEntity = _entity->getModelObject()->getOgreEntity();
			for ( size_t entity_index = 0; entity_index < ogreEntity->getNumSubEntities(); entity_index++ )
			{
				MaterialPtr material = ogreEntity->getSubEntity(entity_index)->getMaterial();
				for ( size_t techIndex = 0; techIndex < material->getNumTechniques(); techIndex++ )
				{
					Technique* technique = material->getTechnique(techIndex);
					for ( size_t passIndex = 0; passIndex < technique->getNumPasses(); passIndex++ )
					{
						Pass* ins_pass = technique->getPass(passIndex);

						Str8 vertex_program_name;
						ins_pass->setVertexProgram(vertex_program_name);

						for ( size_t textureIndex = 0; textureIndex < ins_pass->getNumTextureUnitStates(); textureIndex++ )
						{
							TextureUnitState* texture = ins_pass->getTextureUnitState(textureIndex);
							if ( texture )
							{
								texture->setTextureScroll(uv_start.x, uv_start.y);
								texture->setScrollAnimation(uv_speed.x, uv_speed.y);
							}
						}
					}
				}
			}
			
		}
	}
	//-----------------------------------------------------------------------------------------------------
	void EngineUtil::setDepthCheck(IEntity* entity, bool enabled)
	{
		Entity* _entity = dynamic_cast<Entity*>(entity);
		if ( _entity && _entity->getModelObject() )
		{
			Ogre::Entity* ogreEntity = _entity->getModelObject()->getOgreEntity();
			for ( size_t entity_index = 0; entity_index < ogreEntity->getNumSubEntities(); entity_index++ )
			{
				MaterialPtr material = ogreEntity->getSubEntity(entity_index)->getMaterial();
				for ( size_t techIndex = 0; techIndex < material->getNumTechniques(); techIndex++ )
				{
					Technique* technique = material->getTechnique(techIndex);
					for ( size_t passIndex = 0; passIndex < technique->getNumPasses(); passIndex++ )
					{
						Pass* ins_pass = technique->getPass(passIndex);
						if ( ins_pass )
							ins_pass->setDepthCheckEnabled( enabled );
					}
				}
			}
		}
	}
	//-----------------------------------------------------------------------------------------------------
	void EngineUtil::setMaterialAmbient(IEntity* entity, MG::Color color)
	{
		Entity* _entity = dynamic_cast<Entity*>(entity);
		if ( _entity && _entity->getModelObject() )
		{
			Ogre::Entity* ogreEntity = _entity->getModelObject()->getOgreEntity();
			for ( size_t entity_index = 0; entity_index < ogreEntity->getNumSubEntities(); entity_index++ )
			{
				MaterialPtr material = ogreEntity->getSubEntity(entity_index)->getMaterial();
				for ( size_t techIndex = 0; techIndex < material->getNumTechniques(); techIndex++ )
				{
					Technique* technique = material->getTechnique(techIndex);
					technique->setAmbient(ColourValue(color.r, color.g, color.b, color.a));
				}
			}
		}
	}
	//-----------------------------------------------------------------------------------------------------
	void EngineUtil::setMaterialShiness(IEntity* entity, Flt shiness)
	{
		Entity* _entity = dynamic_cast<Entity*>(entity);
		if ( _entity && _entity->getModelObject() )
		{
			Ogre::Entity* ogreEntity = _entity->getModelObject()->getOgreEntity();
			for ( size_t entity_index = 0; entity_index < ogreEntity->getNumSubEntities(); entity_index++ )
			{
				MaterialPtr material = ogreEntity->getSubEntity(entity_index)->getMaterial();
				for ( size_t techIndex = 0; techIndex < material->getNumTechniques(); techIndex++ )
				{
					Technique* technique = material->getTechnique(techIndex);
					technique->setShininess( shiness );
				}
			}
		}
	}
}

/******************************************************************************/