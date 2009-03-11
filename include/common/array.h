/*                   A R R A Y . H
 * BRL-CAD
 *
 * Copyright (c) 1997-2009 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */

/** @file Array.h
 *
 *  Description -
 *      
 *
 *  Author - David Loman
 *
 */

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "iBME/iBMECommon.h"

#include <new>

	template <typename T>
		class array
		{
		protected:
			T* _data;
			size_t _size;

		public:
			array() throw ()
			{
				_data = 0;
				_size = 0;
			}

			array(size_t size) throw (std::bad_alloc)
			{
				if (size)
				{
					_data = (T*) malloc(size * sizeof(T));
					if (_data == 0)
						throw std::bad_alloc();
				}
				else
					_data = 0;
				_size = size;
			}

			array(const T* data, size_t size) throw (std::bad_alloc)
			{
				_data = (T*) malloc(size * sizeof(T));
				if (_data == 0)
					throw std::bad_alloc();
				_size = size;
				memcpy(_data, data, _size * sizeof(T));
			}

			array(const array& _copy) throw (std::bad_alloc)
			{
				if (_copy._size)
				{
					_data = (T*) malloc(_copy._size * sizeof(T));
					if (_data == 0)
						throw std::bad_alloc();
					_size = _copy._size;
					memcpy(_data, _copy._data, _size * sizeof(T));
				}
				else
				{
					_data = 0;
					_size = 0;
				}
			}

			~array() throw ()
			{
				if (_data)
					free(_data);
			}

			array* clone() const throw (std::bad_alloc)
			{
				return new array(*this);
			}

			const array& operator=(const array& _set) throw (std::bad_alloc)
			{
				resize(_set._size);
				if (_size)
					memcpy(_data, _set._data, _size * sizeof(T));

				return *this;
			}

			bool operator==(const array& _cmp) const throw ()
			{
				if (_size != _cmp._size)
					return false;

				if (_size == 0 && _cmp._size == 0)
					return true;

				return !memcmp(_data, _cmp._data, _size * sizeof(T));
			}

			bool operator!=(const array& _cmp) const throw ()
			{
				if (_size != _cmp._size)
					return true;

				if (_size == 0 && _cmp._size == 0)
					return false;

				return memcmp(_data, _cmp._data, _size * sizeof(T));
			}

			T* data() throw ()
			{
				return _data;
			}

			const T* data() const throw ()
			{
				return _data;
			}

			size_t size() const throw ()
			{
				return _size;
			}

			void replace(T* data, size_t size) throw ()
			{
				if (_data)
					free(_data);

				_data = data;
				_size = size;
			}

			void swap(array& _swp) throw ()
			{
				T* tmp_data = _swp._data;
				size_t tmp_size = _swp._size;

				_swp._data = _data;
				_swp._size = _size;

				_data = tmp_data;
				_size = tmp_size;
			}

			void resize(size_t _newsize) throw (std::bad_alloc)
			{
				if (_newsize)
				{
					if (_newsize != _size)
					{
						_data = (T*) (_data ? realloc(_data, _newsize * sizeof(T)) : malloc(_newsize * sizeof(T)));
						if (_data == 0)
							throw std::bad_alloc();
					}
				}
				else
				{
					if (_data)
					{
						free(_data);
						_data = 0;
					}
				}
				_size = _newsize;
			}

			T& operator[](size_t _n) throw ()
			{
				return _data[_n];
			}

			const T operator[](size_t _n) const throw ()
			{
				return _data[_n];
			}

			const array<T>& operator+=(const array<T>& _rhs) throw ()
			{
				if (_rhs._size)
				{
					size_t _curr = _size;
					resize(_size+_rhs._size);
					memcpy(_data+_curr, _rhs._data, _rhs._size * sizeof(T));
				}
				return *this;
			}

			
			void printMe()
			{
				for (int i = 0; i < _size ; ++i)
				{
					std::cout << _data[i];
				}
				std::cout << std::endl;
			}


		};

	template<typename T>
		array<T> operator+(const array<T>& _lhs, const array<T>& _rhs)
		{
			array<T> _con(_lhs);

			return _con += _rhs;
		};


#endif

// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
