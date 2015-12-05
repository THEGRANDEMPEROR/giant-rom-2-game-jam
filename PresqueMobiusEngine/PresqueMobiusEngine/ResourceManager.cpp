#include "ResourceManager.h"
#include "Engine.h"

ResourceManager::ResourceManager() {

}

ResourceManager::~ResourceManager() {

}

resourceStruct* ResourceManager::getResource(LPCSTR fileName, resourceType type) {
	resourceStruct tempRes;
	imageAsset tempImage;
	cubeAsset tempCube;
	modelAsset tempModel;
	soundStruct tempSound;
	musicStruct tempMusic;
	for(int i = 0; i < resVec.size(); ++i) {
		if(resVec[i].resType == type) {
			if(resVec[i].name == fileName) {
				return &resVec[i];
			}
		}
	}
	tempRes.name = fileName;
	tempRes.resType = type;
	switch(type) {
	case image:
		Engine::instance()->getvFrame()->loadImage(fileName,&tempImage);
		imageList.push_back(tempImage);
		tempRes.resource = &imageList.back();
		break;
	case cube:
		return NULL;
		break;
	case xModel:
		Engine::instance()->getvFrame()->loadXModel(fileName,&tempModel);
		for(int i = 0; i < tempModel.numMats; ++i) {
			tempModel.textures[i] = (imageAsset*)getResource(tempModel.mats->pTextureFilename,image)->resource;
		}
		modelList.push_back(tempModel);
		tempRes.resource = &modelList.back();
		break;
	case audio:
		Engine::instance()->getsFrame()->load(fileName,&tempSound.asset);
		tempSound.minDist = defaultMinSound;
		tempSound.maxDist = defaultMaxSound;
		tempSound.type = soundEffect;
		soundList.push_back(tempSound);
		tempRes.resource = &soundList.back();
		break;
	case stream:
		Engine::instance()->getsFrame()->loadStream(fileName,&tempMusic.asset);
		tempMusic.type = music;
		musicList.push_back(tempMusic);
		tempRes.resource = &musicList.back();
		break;
	default:
		break;
	}
	resVec.push_back(tempRes);
	return &resVec[resVec.size()-1];
}

resourceStruct* ResourceManager::getResource(LPCSTR name, D3DXCOLOR mask) {
	resourceStruct tempRes;
	imageAsset tempImage;
	tempRes.name = name;
	tempRes.resType = image;
	Engine::instance()->getvFrame()->loadImage(name,mask,&tempImage);
	imageList.push_back(tempImage);
	tempRes.resource = &imageList.back();

	return &resVec[resVec.size()-1];
}

resourceStruct* ResourceManager::createCube(LPCSTR name, float top, float bottom, float front, float back, float left, float right) {
	cubeAsset tempCube;
	resourceStruct tempRes;

	tempRes.name = name;
	tempRes.resType = cube;
	Engine::instance()->getvFrame()->createCube(&tempCube,top,bottom,front,back,left,right);

	cubeList.push_back(tempCube);
	tempRes.resource = &cubeList.back();
	resVec.push_back(tempRes);
	return &resVec[resVec.size()-1];
}

void ResourceManager::reload() {
	imageAsset* tempImage;
	cubeAsset* tempCube;
	modelAsset* tempModel;
	soundStruct* tempSound;
	musicStruct* tempMusic;
	for(int i = 0; i < resVec.size(); ++i) {
		switch(resVec[i].resType) {
		case image:
			tempImage = (imageAsset*)resVec[i].resource;
			tempImage->objTex->Release();
			Engine::instance()->getvFrame()->loadImage(resVec[i].name.c_str(),tempImage->mask,tempImage);
			break;
		case cube:
			tempCube = (cubeAsset*)resVec[i].resource;
			tempCube->objDec->Release();
			tempCube->objInd->Release();
			tempCube->obj->Release();
			Engine::instance()->getvFrame()->createCube(tempCube,tempCube->top,tempCube->bottom,tempCube->front,tempCube->back,tempCube->left,tempCube->right);
			break;
		case xModel:
			tempModel = (modelAsset*)resVec[i].resource;
			tempModel->adj->Release();
			tempModel->adj = 0;
			tempModel->matPoint->Release();
			tempModel->matPoint = 0;
			tempModel->mesh->Release();
			tempModel->mesh = 0;
			/*tempModel->dec->Release();
			tempModel->dec = 0;*/
			delete [] tempModel->textures;
			tempModel->numMats = 0;
			Engine::instance()->getvFrame()->loadXModel(resVec[i].name.c_str(),tempModel);
			for(int i = 0; i < tempModel->numMats; ++i) {
				tempModel->textures[i] = (imageAsset*)getResource(tempModel->mats->pTextureFilename,image)->resource;
			}
			break;
		case audio:
			tempSound = (soundStruct*)resVec[i].resource;
			tempSound->asset->release();
			Engine::instance()->getsFrame()->load(resVec[i].name.c_str(),&tempSound->asset);
			break;
		case stream:
			tempMusic = (musicStruct*)resVec[i].resource;
			tempMusic->asset->release();
			Engine::instance()->getsFrame()->loadStream(resVec[i].name.c_str(),&tempMusic->asset);
			break;
		default:
			break;
		}
	}
}

void ResourceManager::reload(LPCSTR fileName) {
	imageAsset* tempImage;
	cubeAsset* tempCube;
	modelAsset* tempModel;
	soundStruct* tempSound;
	musicStruct* tempMusic;
	for(int i = 0; i < resVec.size(); ++i) {
		if(resVec[i].name == fileName) {
			switch(resVec[i].resType) {
			case image:
				tempImage = (imageAsset*)resVec[i].resource;
				tempImage->objTex->Release();
				Engine::instance()->getvFrame()->loadImage(resVec[i].name.c_str(),tempImage);
				break;
			case cube:
				tempCube = (cubeAsset*)resVec[i].resource;
				tempCube->objDec->Release();
				tempCube->objInd->Release();
				tempCube->obj->Release();
				Engine::instance()->getvFrame()->createCube(tempCube,tempCube->top,tempCube->bottom,tempCube->front,tempCube->back,tempCube->left,tempCube->right);
				break;
			case xModel:
				tempModel = (modelAsset*)resVec[i].resource;
				tempModel->adj->Release();
				tempModel->adj = 0;
				tempModel->matPoint->Release();
				tempModel->matPoint = 0;
				tempModel->mesh->Release();
				tempModel->mesh = 0;
				/*tempModel->dec->Release();
				tempModel->dec = 0;*/
				delete [] tempModel->textures;
				tempModel->numMats = 0;
				Engine::instance()->getvFrame()->loadXModel(resVec[i].name.c_str(),tempModel);
				for(int i = 0; i < tempModel->numMats; ++i) {
					tempModel->textures[i] = (imageAsset*)getResource(tempModel->mats->pTextureFilename,image)->resource;
				}
				break;
			case audio:
				tempSound = (soundStruct*)resVec[i].resource;
				tempSound->asset->release();
				Engine::instance()->getsFrame()->load(resVec[i].name.c_str(),&tempSound->asset);
				break;
			case stream:
				tempMusic = (musicStruct*)resVec[i].resource;
				tempMusic->asset->release();
				Engine::instance()->getsFrame()->loadStream(resVec[i].name.c_str(),&tempMusic->asset);
				break;
			default:
				break;
			}
		}
	}
}

void ResourceManager::reload(resourceType type) {
	imageAsset* tempImage;
	cubeAsset* tempCube;
	modelAsset* tempModel;
	soundStruct* tempSound;
	musicStruct* tempMusic;

	for(int i = 0; i < resVec.size(); ++i) {
		if(resVec[i].resType == type) {
			switch(type) {
			case image:
				tempImage = (imageAsset*)resVec[i].resource;
				tempImage->objTex->Release();
				Engine::instance()->getvFrame()->loadImage(resVec[i].name.c_str(),tempImage);
				break;
			case cube:
				tempCube = (cubeAsset*)resVec[i].resource;
				tempCube->objDec->Release();
				tempCube->objInd->Release();
				tempCube->obj->Release();
				Engine::instance()->getvFrame()->createCube(tempCube,tempCube->top,tempCube->bottom,tempCube->front,tempCube->back,tempCube->left,tempCube->right);
				break;
			case xModel:
				tempModel = (modelAsset*)resVec[i].resource;
				tempModel->adj->Release();
				tempModel->adj = 0;
				tempModel->matPoint->Release();
				tempModel->matPoint = 0;
				tempModel->mesh->Release();
				tempModel->mesh = 0;
				/*tempModel->dec->Release();
				tempModel->dec = 0;*/
				delete [] tempModel->textures;
				tempModel->numMats = 0;
				Engine::instance()->getvFrame()->loadXModel(resVec[i].name.c_str(),tempModel);
				for(int i = 0; i < tempModel->numMats; ++i) {
					tempModel->textures[i] = (imageAsset*)getResource(tempModel->mats->pTextureFilename,image)->resource;
				}
				break;
			case audio:
				tempSound = (soundStruct*)resVec[i].resource;
				tempSound->asset->release();
				Engine::instance()->getsFrame()->load(resVec[i].name.c_str(),&tempSound->asset);
				break;
			case stream:
				tempMusic = (musicStruct*)resVec[i].resource;
				tempMusic->asset->release();
				Engine::instance()->getsFrame()->loadStream(resVec[i].name.c_str(),&tempMusic->asset);
				break;
			default:
				break;
			}
		}
	}
}

void ResourceManager::release() {
	while(imageList.size() > 0) {
		imageList.back().objTex->Release();
		imageList.pop_back();
	}
	while(cubeList.size() > 0) {
		cubeList.back().objInd->Release();
		cubeList.back().objDec->Release();
		cubeList.back().obj->Release();
		cubeList.pop_back();
	}
	while(modelList.size() > 0) {
		modelList.back().adj->Release();
		modelList.back().adj = 0;
		modelList.back().matPoint->Release();
		modelList.back().matPoint = 0;
		modelList.back().mesh->Release();
		modelList.back().mesh = 0;
		/*modelList.back().dec->Release();
		modelList.back().dec = 0;*/
		delete [] modelList.back().textures;
		modelList.back().numMats = 0;
		modelList.pop_back();
	}
	while(soundList.size() > 0) {
		soundList.back().asset->release();
		soundList.pop_back();
	}
	while(musicList.size() > 0) {
		musicList.back().asset->release();
		musicList.pop_back();
	}
	resVec.clear();
}