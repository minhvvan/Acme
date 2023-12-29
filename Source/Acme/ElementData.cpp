// Fill out your copyright notice in the Description page of Project Settings.


#include "ElementData.h"

void UElementData::SetElement(EElement e)
{
	Element = e;
}

EElement UElementData::GetElement()
{
	return Element;
}
