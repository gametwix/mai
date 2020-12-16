#pragma once

#include <iostream>
#include <memory>
#include "Pentagon.hpp"
#include "Rhomb.hpp"
#include <utility>

template <class TDot,class Fig>
class Factory{};

template <class TDot>
class Factory<TDot,Rhomb<TDot>>
{

};