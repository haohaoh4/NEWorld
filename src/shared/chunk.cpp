#include "chunk.h"
#include "pluginmanager.h"
#include <algorithm>

void NWAPICALL DefaultChunkGen(const Vec3i*, BlockData* blocks, int32_t daylightBrightness)
{
    // This is the default terrain generator. Use this when no generators were loaded from plugins.
    for (int x = 0; x < Chunk::Size; x++)
        for (int z = 0; z < Chunk::Size; z++)
            for (int y = 0; y < Chunk::Size; y++)
                blocks[x*Chunk::Size*Chunk::Size + y*Chunk::Size + z] = BlockData(0, daylightBrightness, 0);
}

bool ChunkGeneratorLoaded = false;
ChunkGenerator *ChunkGen = &DefaultChunkGen;

void Chunk::build(int daylightBrightness)
{
    (*ChunkGen)(&getPosition(), getBlocks(), daylightBrightness);
    setUpdated(true);
}
