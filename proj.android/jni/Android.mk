LOCAL_PATH := $(call my-dir)
ADX2_PATH := $(LOCAL_PATH)../../adx2

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cri_ware_cocos2dx
LOCAL_SRC_FILES := ../../adx2/libs/android/armeabi-v7a/libcri_ware_android_LE.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   ../../Classes/AppDelegate.cpp \
				   ../../Classes/Base/GameMaster.cpp \
				   ../../Classes/Base/Player.cpp \
				   ../../Classes/Base/UI.cpp \
				   ../../Classes/Base/Unit.cpp \
				   ../../Classes/Base/Sprite3D.cpp \
				   ../../Classes/Scene/GameModelsLayer.cpp \
				   ../../Classes/Scene/GameScene.cpp \
				   ../../Classes/Scene/GameUILayer.cpp \
				   ../../Classes/Scene/TestScene.cpp \
				   ../../Classes/Scene/TitleScene.cpp \
				   ../../Classes/System/Sound.cpp \
				   ../../Classes/Object/Muzzle.cpp \
				   ../../Classes/Stage/Enemy.cpp \
				   ../../Classes/Stage/EnemyTable.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(ADX2_PATH)/include/android

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END

# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

	-llog \
	-lOpenSLES
LOCAL_SHARED_LIBRARIES := librci_ware_cocos2dx