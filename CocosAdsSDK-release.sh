rm -rf sdk
mkdir sdk
mkdir sdk/Classes
classPath="demo/Classes/"
cp ${classPath}"CocosAds.h" ${classPath}"CocosAds-android.cpp" ${classPath}"CocosAds-ios.mm" sdk/Classes/

helperPath="demo/proj.android/src/com/"
mkdir sdk/com
cp -rf ${helperPath} sdk/com
