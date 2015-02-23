
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
				\
                   ../../Classes/Base/GameMaster.cpp \
                   ../../Classes/Base/Player.cpp \
                   ../../Classes/Base/UI.cpp \
                   ../../Classes/Base/Unit.cpp \
                   ../../Classes/Base/Sprite3D.cpp \
				\
				   ../../Classes/Object/Muzzle.cpp \
				\
				   ../../Classes/Scene/Character.cpp \
				   ../../Classes/Scene/CreditScene.cpp \
                   ../../Classes/Scene/GameModelsLayer.cpp \
                   ../../Classes/Scene/GameScene.cpp \
                   ../../Classes/Scene/GameUILayer.cpp \
                   ../../Classes/Scene/TestScene.cpp \
                   ../../Classes/Scene/TitleScene.cpp \
				\
				   ../../Classes/Stage/Enemy.cpp \
                   ../../Classes/Stage/EnemyTable.cpp \
				\
				   ../../Classes/System/ResourceLoader.cpp \
				   ../../Classes/System/Sound.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
