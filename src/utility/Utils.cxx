
/*                     U T I L S. C X X
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file utils.cxx
 *
 * Brief description
 *
 */

#include "Utility/Utils.h"


QUuid* 
Utils::getQUuid(QDataStream* ds)
{
  QString* strUUID = Utils::getString(ds);

  //std::cout << strUUID->toStdString();

  QUuid* out = new QUuid(*strUUID);

  delete strUUID;

  return out;
}

void
Utils::putQUuid(QDataStream* ds, QUuid uuid)
{
  Utils::putString(ds, uuid.toString());
}


QString* Utils::getString(QDataStream* ds)
{
  
  quint32 len;
  QString* out = new QString();

  //get str length
  *ds >> len;

  //std::cout << "Read String length of: " << len << std::endl;

  for (quint32 i = 0; i< len; ++i)
    {
      quint16 shrt;
      *ds >> shrt;

      QChar c(shrt);

      out->append(c);
    }

  /*
  std::cout << "\ngetString:" << std::endl;
  std::cout << out->size() << std::endl;
  std::cout << out->toStdString() << std::endl;
  */

  return out;
  
}

void Utils::putString(QDataStream* ds, QString str)
{
  /*
  std::cout << "\nputString:" << std::endl;
  std::cout << str.size() << std::endl;
  std::cout << str.toStdString() << std::endl;
  */

  *ds << str.size();

  for (quint32 i = 0; i< str.size(); ++i)
    {
      quint16 shrt = str.at(i).unicode();
      *ds << str.at(i).unicode();
    }

}

void Utils::printQByteArray(QByteArray* ba) 
{
  std::cout << std::endl;

  quint32 size = ba->size();

  std::cout << "ByteArray.Size(): " << size << std::endl;

  for (quint32 i = 0; i < size; ++i)
    {
      char c = ba->at(i);
      std::cout << QString::number(c).toStdString() << " '" << c << "', ";
      
      if ((i + 1) % 25 == 0) {
          std::cout << std::endl;
      }
    }
  std::cout << std::endl << std::endl;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
