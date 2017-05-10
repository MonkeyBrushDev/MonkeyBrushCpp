/*
 * Copyright (c) 2016 maldicion069
 *
 * Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
 *
 * This file is part of MonkeyBrushPlusPlus
 * <https://github.com/maldicion069/monkeybrushplusplus>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "Layer.hpp"

namespace mb
{
  // Based on https://www.tutorialspoint.com/cplusplus/cpp_bitwise_operators.htm

  // Default mask as 0
  Layer::Layer()
  : _mask(1) {}
  void Layer::set(const int& channel)
  {
    this->_mask = 1 << channel;
  }
  void Layer::set(const std::string& layer)
  {
    set(Layer::layerNameToID(layer));
  }
  void Layer::enable(const int& channel)
  {
    this->_mask |= 1 << channel;
  }
  void Layer::enable(const std::string& layer)
  {
    enable(Layer::layerNameToID(layer));
  }
  void Layer::toggle(const int& channel)
  {
    this->_mask ^= 1 << channel;
  }
  void Layer::toggle(const std::string& layer)
  {
    toggle(Layer::layerNameToID(layer));
  }
  void Layer::disable(const int& channel)
  {
    this->_mask &= ~(1 << channel);
  }
  void Layer::disable(const std::string& layer)
  {
    disable(Layer::layerNameToID(layer));
  }
  bool Layer::check(const Layer& layer2) const
  {
    return (this->_mask & layer2._mask) != 0;
  }
  bool Layer::check(const int& channel) const
  {
    return (this->_mask & (1 << channel)) != 0;
  }
  bool Layer::check(const std::string& layer) const
  {
    return check(Layer::layerNameToID(layer));
  }
  std::string LayerLookup::name(const int& channel)
  {
    if (!LayerLookup::_initialized)
    {
      LayerLookup::initialize();
    }
    return LayerLookup::_names[channel];
  }
  void LayerLookup::name(const std::string name, const int& index)
  {
    if (!LayerLookup::_initialized)
    {
      LayerLookup::initialize();
    }
    LayerLookup::_names[index] = name;
  }
  void LayerLookup::initialize()
  {
    if (!LayerLookup::_initialized)
    {
      LayerLookup::_names[0] = "Default";
      LayerLookup::_names[1] = "Layer1";
      for (unsigned int i = 2; i < 32; ++i)
      {
        LayerLookup::_names[i] = "Empty";
      }
      LayerLookup::_initialized = true;
    }
  }
  int LayerLookup::nameToID(const std::string& layer)
  {
    for (int i = 0; i < 32; ++i)
    {
      if (layer == LayerLookup::_names[i])
      {
        return i;
      }
    }
    throw;
  }
  int Layer::layerNameToID(const std::string& layer)
  {
    return LayerLookup::nameToID(layer);
  }

  std::array<std::string, 32> LayerLookup::_names;
  bool LayerLookup::_initialized;
}
