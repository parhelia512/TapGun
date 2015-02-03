LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/C++/Base/GameMaster.cpp \
                   ../../Classes/C++/Base/Player.cpp \
                   ../../Classes/C++/Base/UI.cpp \
                   ../../Classes/C++/Base/Unit.cpp \
                   ../../Classes/C++/Base/Sprite3D.cpp \
                   ../../Classes/C++/Scene/GameModelsLayer.cpp \
                   ../../Classes/C++/Scene/GameScene.cpp \
                   ../../Classes/C++/Scene/GameUILayer.cpp \
                   ../../Classes/C++/Scene/TestScene.cpp \
                   ../../Classes/C++/Scene/TitleScene.cpp \
                   ../../Classes/C++/System/Sound.cpp \

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
