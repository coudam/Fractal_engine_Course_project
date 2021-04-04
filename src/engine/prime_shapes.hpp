#pragma once

const float plane[] = {
    -1.f, 0.f, -1.f,
    -1.f, 0.f, 1.f,
    1.f, 0.f, -1.f,

    1.f, 0.f, -1.f,
    -1.f, 0.f, 1.f,
    1.f, 0.f, 1.f
};

const float plane_normals[] = {
    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,

    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,
    0.f, -1.f, 0.f,
};

const float plane_uvs[] = {
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,

    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
};


const float voxel[] = {
	-1.f, 1.f, 1.f,
    1.f, 1.f, 1.f,
    -1.f, -1.f, 1.f,
    1.f, -1.f, 1.f,
    1.f, -1.f, -1.f,
    1.f, 1.f, 1.f,
    1.f, 1.f, -1.f,
    -1.f, 1.f, 1.f,
    -1.f, 1.f, -1.f,
    -1.f, -1.f, 1.f,
    -1.f, -1.f, -1.f,
    1.f, -1.f, -1.f,
    -1.f, 1.f, -1.f,
    1.f, 1.f, -1.f
};

const float voxel_normals[] = {
    -1.f, 1.f, 1.f,
    1.f, 1.f, 1.f,
    -1.f, -1.f, 1.f,
    1.f, -1.f, 1.f,
    1.f, -1.f, -1.f,
    1.f, 1.f, 1.f,
    1.f, 1.f, -1.f,
    -1.f, 1.f, 1.f,
    -1.f, 1.f, -1.f,
    -1.f, -1.f, 1.f,
    -1.f, -1.f, -1.f,
    1.f, -1.f, -1.f,
    -1.f, 1.f, -1.f,
    1.f, 1.f, -1.f
};

const float voxel_uvs[] = {
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 0.0f
};

const float triangle[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f
};
