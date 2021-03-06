#pragma once
#include "cashgen.h"
#include "CGTerrainManager.h"
#include "CGTerrainConfig.h"

struct FCGJob;

class FCGTerrainGeneratorWorker : public FRunnable
{

	ACGTerrainManager* pTerrainManager;
	FCGTerrainConfig* pTerrainConfig;
	TQueue<FCGJob, EQueueMode::Spsc>* inputQueue;
	FCGJob workJob;
	uint8 workLOD;

	TArray<FVector>*	pVertices;
	TArray<int32>*		pTriangles;
	TArray<FVector>*	pNormals;
	TArray<FVector2D>*	pUV0;
	TArray<FColor>*		pVertexColors;
	TArray<FRuntimeMeshTangent>* pTangents;
	TArray<FVector>* pHeightMap;
	TArray<float>* pDepositionMap;

	bool IsThreadFinished;

	void prepMaps();
	void ProcessTerrainMap();
	void AddDepositionToHeightMap();
	void ProcessSingleDropletErosion();
	void ProcessPerBlockGeometry();
	void ProcessPerVertexTasks();
	void ProcessSkirtGeometry();

	void erodeHeightMapAtIndex(int32 aX, int32 aY, float aAmount);
	FVector GetNormalFromHeightMapForVertex(const int32 vertexX, const int32 vertexY);
	FRuntimeMeshTangent GetTangentFromNormal(const FVector aNormal);
	void UpdateOneBlockGeometry(const int aX, const int aY, int32& aVertCounter, int32& triCounter);

	int32 GetNumberOfNoiseSamplePoints();

public:

	FCGTerrainGeneratorWorker(ACGTerrainManager* aTerrainManager,
		FCGTerrainConfig* aTerrainConfig,
		TQueue<FCGJob, EQueueMode::Spsc>* anInputQueue);

	virtual ~FCGTerrainGeneratorWorker();

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();

};


