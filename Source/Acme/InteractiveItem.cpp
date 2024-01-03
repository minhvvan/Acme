// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveItem.h"

void AInteractiveItem::Init(EItemName itemKey)
{
	//Info Setting
	Mesh->SetStaticMesh(Meshes[itemKey]);
}
