#include "ExternalButton.h"
#include"ExternalButtonDispatcher.h"
ExternalButton::ExternalButton(shared_ptr<ExternalButtonDispatcher>externalDispatcher):
externalDispatcher(externalDispatcher)
{
}

ExternalButton::~ExternalButton()
{
}

void ExternalButton::pressButton(int floor,Direction dir)
{
    externalDispatcher->submitRequest(floor,dir);
}