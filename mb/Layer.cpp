/**
 * Copyright (c) 2017, Monkey Brush
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#include "Layer.hpp"
#include <fstream>
#include <sstream>

namespace mb
{
  // Based on https://www.tutorialspoint.com/cplusplus/cpp_bitwise_operators.htm

  // Default mask as 0
  Layer::Layer( void )
  : _mask( 1 )
  {
  }
  void Layer::set( const int& channel)
  {
    this->_mask = 1 << channel;
  }
  void Layer::set( const std::string& layer)
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
  const std::string LayerLookup::getName(const int& channel)
  {
    if (!LayerLookup::_initialized)
    {
      LayerLookup::initialize();
    }
    return LayerLookup::_names[channel];
  }
  void LayerLookup::setName(const std::string& name, const int& index)
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
      for ( unsigned int i = 1; i < 32; ++i )
      {
        LayerLookup::_names[i] = std::string( "Layer" ) + std::to_string( i );
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

  void LayerLookup::loadFromFile( const std::string& file )
  {
    std::ifstream inFile( file.c_str( ) );
    std::string layerName;
    unsigned int i = 0;
    while( !inFile.eof( ) )
    {
      if ( i >=32 ) throw;
      inFile >> layerName;
      LayerLookup::setName( layerName, i );
      i++;
    }
  }

  std::array<std::string, 32> LayerLookup::_names;
  bool LayerLookup::_initialized;
}
