﻿/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "chunkclient.h"
#include "../protocol/gen/s2c/2-Chunk_generated.h"
#include "worldclient.h"

VertexArray ChunkClient::va(262144, VertexFormat(2, 3, 0, 3));
bool ChunkClient::mergeFace;

void ChunkClient::renderBlock(BlockTexCoord coord[], const Vec3i& pos)
{
    Vec3i worldpos = getPosition() * Size + pos;

    BlockData curr = getBlock(pos);
    BlockData neighbors[6] =
    {
        pos.x == Size - 1 ? mWorld.getBlock(Vec3i(worldpos.x + 1, worldpos.y, worldpos.z)) : getBlock(Vec3i(pos.x + 1, pos.y, pos.z)),
        pos.x == 0 ? mWorld.getBlock(Vec3i(worldpos.x - 1, worldpos.y, worldpos.z)) : getBlock(Vec3i(pos.x - 1, pos.y, pos.z)),
        pos.y == Size - 1 ? mWorld.getBlock(Vec3i(worldpos.x, worldpos.y + 1, worldpos.z)) : getBlock(Vec3i(pos.x, pos.y + 1, pos.z)),
        pos.y == 0 ? mWorld.getBlock(Vec3i(worldpos.x, worldpos.y - 1, worldpos.z)) : getBlock(Vec3i(pos.x, pos.y - 1, pos.z)),
        pos.z == Size - 1 ? mWorld.getBlock(Vec3i(worldpos.x, worldpos.y, worldpos.z + 1)) : getBlock(Vec3i(pos.x, pos.y, pos.z + 1)),
        pos.z == 0 ? mWorld.getBlock(Vec3i(worldpos.x, worldpos.y, worldpos.z - 1)) : getBlock(Vec3i(pos.x, pos.y, pos.z - 1)),
    };

    // Right
    if (adjacentTest(curr, neighbors[0]))
        va.addPrimitive(4,
    {
        coord[0].d[0], coord[0].d[1], 0.5f, 0.5f, 0.5f, pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f,
        coord[0].d[0], coord[0].d[3], 0.5f, 0.5f, 0.5f, pos.x + 1.0f, pos.y + 0.0f, pos.z + 1.0f,
        coord[0].d[2], coord[0].d[3], 0.5f, 0.5f, 0.5f, pos.x + 1.0f, pos.y + 0.0f, pos.z + 0.0f,
        coord[0].d[2], coord[0].d[1], 0.5f, 0.5f, 0.5f, pos.x + 1.0f, pos.y + 1.0f, pos.z + 0.0f
    });

    // Left
    if (adjacentTest(curr, neighbors[1]))
        va.addPrimitive(4,
    {
        coord[1].d[0], coord[1].d[1], 0.5f, 0.5f, 0.5f, pos.x + 0.0f, pos.y + 1.0f, pos.z + 0.0f,
        coord[1].d[0], coord[1].d[3], 0.5f, 0.5f, 0.5f, pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f,
        coord[1].d[2], coord[1].d[3], 0.5f, 0.5f, 0.5f, pos.x + 0.0f, pos.y + 0.0f, pos.z + 1.0f,
        coord[1].d[2], coord[1].d[1], 0.5f, 0.5f, 0.5f, pos.x + 0.0f, pos.y + 1.0f, pos.z + 1.0f
    });

    // Top
    if (adjacentTest(curr, neighbors[2]))
        va.addPrimitive(4,
    {
        coord[2].d[0], coord[2].d[1], 1.0f, 1.0f, 1.0f, pos.x + 0.0f, pos.y + 1.0f, pos.z + 0.0f,
        coord[2].d[0], coord[2].d[3], 1.0f, 1.0f, 1.0f, pos.x + 0.0f, pos.y + 1.0f, pos.z + 1.0f,
        coord[2].d[2], coord[2].d[3], 1.0f, 1.0f, 1.0f, pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f,
        coord[2].d[2], coord[2].d[1], 1.0f, 1.0f, 1.0f, pos.x + 1.0f, pos.y + 1.0f, pos.z + 0.0f
    });

    // Bottom
    if (adjacentTest(curr, neighbors[3]))
        va.addPrimitive(4,
    {
        coord[3].d[0], coord[3].d[1], 1.0f, 1.0f, 1.0f, pos.x + 0.0f, pos.y + 0.0f, pos.z + 1.0f,
        coord[3].d[0], coord[3].d[3], 1.0f, 1.0f, 1.0f, pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f,
        coord[3].d[2], coord[3].d[3], 1.0f, 1.0f, 1.0f, pos.x + 1.0f, pos.y + 0.0f, pos.z + 0.0f,
        coord[3].d[2], coord[3].d[1], 1.0f, 1.0f, 1.0f, pos.x + 1.0f, pos.y + 0.0f, pos.z + 1.0f
    });

    // Front
    if (adjacentTest(curr, neighbors[4]))
        va.addPrimitive(4,
    {
        coord[4].d[0], coord[4].d[1], 0.7f, 0.7f, 0.7f, pos.x + 0.0f, pos.y + 1.0f, pos.z + 1.0f,
        coord[4].d[0], coord[4].d[3], 0.7f, 0.7f, 0.7f, pos.x + 0.0f, pos.y + 0.0f, pos.z + 1.0f,
        coord[4].d[2], coord[4].d[3], 0.7f, 0.7f, 0.7f, pos.x + 1.0f, pos.y + 0.0f, pos.z + 1.0f,
        coord[4].d[2], coord[4].d[1], 0.7f, 0.7f, 0.7f, pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f
    });

    // Back
    if (adjacentTest(curr, neighbors[5]))
        va.addPrimitive(4,
    {
        coord[5].d[0], coord[5].d[1], 0.7f, 0.7f, 0.7f, pos.x + 1.0f, pos.y + 1.0f, pos.z + 0.0f,
        coord[5].d[0], coord[5].d[3], 0.7f, 0.7f, 0.7f, pos.x + 1.0f, pos.y + 0.0f, pos.z + 0.0f,
        coord[5].d[2], coord[5].d[3], 0.7f, 0.7f, 0.7f, pos.x + 0.0f, pos.y + 0.0f, pos.z + 0.0f,
        coord[5].d[2], coord[5].d[1], 0.7f, 0.7f, 0.7f, pos.x + 0.0f, pos.y + 1.0f, pos.z + 0.0f
    });
}

void ChunkClient::buildVertexArray()
{
    // Notice: the building process shall not fail
    setUpdated(false);

    va.clear();
    if (mergeFace)
    {
        // TODO: merge face rendering
    }
    else
    {
        Vec3i::for_range(0, Size, [&](const Vec3i& pos)
        {
            BlockData b = getBlock(pos);
            BlockRendererManager::render(b.getID(), this, pos);
        });
    }

    mBuffer.update(va);
    mRenderBuilt = true;
}

Chunk* ChunkClient::getFromFlatbuffers(const s2c::Chunk * fbChunk, WorldClient& worlds)
{
    // TODO: Optimize
    Chunk* nwChunk = new ChunkClient({ fbChunk->pos()->x(), fbChunk->pos()->y(), fbChunk->pos()->z() }, worlds);
    for (auto i = 0; i < Size*Size*Size; i++)
        nwChunk->getBlocks()[i] = BlockData(fbChunk->blocks()->Get(i));
    return nwChunk;
}

