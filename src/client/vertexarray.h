/*
* NEWorld: An free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
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
*/

#ifndef VERTEXARRAY_H_
#define VERTEXARRAY_H_

#include <cstring>

class VertexArray
{
    private:
        // Vertex count
        int m_vertexes, m_maxVertexes;
        // Vertex Attribute Count
        int m_textureCount, m_colorCount, m_attributeCount, m_coordinateCount;
        // Vertex Attributes
        float *m_vertexAttributes;
        // Attributes count
        int m_vertexAttributeCount;
        // Array
        float *m_data;

    public:
        VertexArray(int maxVertexes, int textureElementCount, int colorElementCount, int attributeElementCount, int coordinateElementCount)
            :m_maxVertexes(maxVertexes), m_vertexAttributeCount(textureElementCount + colorElementCount + attributeElementCount + coordinateElementCount),
            m_textureCount(textureElementCount), m_colorCount(colorElementCount), m_attributeCount(attributeElementCount), m_coordinateCount(coordinateElementCount)
        {
            m_data = new float[m_maxVertexes*m_vertexAttributeCount];
            m_vertexAttributes = new float[m_vertexAttributeCount];
            clear();
        }
        
        ~VertexArray()
        {
            delete[] m_data;
            delete[] m_vertexAttributes;
        }
        
        void clear()
        {
            memset(m_data, 0, m_maxVertexes*m_vertexAttributeCount*sizeof(float));
            memset(m_vertexAttributes, 0, m_vertexAttributeCount*sizeof(float));
            m_vertexes = 0;
        }

        // Set texture coordinates
        void setTexture(const int size, const float* texture)
        {
            // TODO: Check if (size > m_textureCount)
            memcpy(m_vertexAttributes, texture, size*sizeof(float));
        }

        // Set color value
        void setColor(const int size, const float* color)
        {
            // TODO: Check if (size > m_colorCount)
            memcpy(m_vertexAttributes + m_textureCount, color, size*sizeof(float));
        }

        // Set extra vertex attributes value
        void setAttribute(const int size, const float* attribute)
        {
            // TODO: Check if (size > m_attributeCount)
            memcpy(m_vertexAttributes + m_textureCount + m_colorCount, attribute, size*sizeof(float));
        }

        // Add vertex
        void addVertex(const float* coords)
        {
            memcpy(m_data + m_vertexes*sizeof(float), m_vertexAttributes, m_vertexAttributeCount*sizeof(float));
            memcpy(m_data + m_vertexes + m_vertexAttributeCount*sizeof(float), coords, m_coordinateCount*sizeof(float));
            m_vertexes++;
        }

        // Generate vertex buffer for rendering
        void flush();
        // Render vertex buffer
        static void render();

};

#endif // !VERTEXARRAY_H_
