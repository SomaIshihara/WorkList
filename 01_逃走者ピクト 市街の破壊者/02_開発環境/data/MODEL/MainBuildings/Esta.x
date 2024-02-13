xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 308;
 100.00000;107.99380;80.51570;,
 100.00000;126.77720;100.00000;,
 100.00000;23.08730;100.00000;,
 100.00000;29.25390;80.51570;,
 42.30090;160.84990;-90.63210;,
 89.50090;160.84990;-90.63210;,
 89.50090;124.64990;-90.63210;,
 42.30090;124.64990;-90.63210;,
 89.50090;160.84990;-90.63210;,
 89.50090;160.84990;-39.93210;,
 89.50090;124.64990;-39.93210;,
 89.50090;124.64990;-90.63210;,
 89.50090;160.84990;-39.93210;,
 42.30090;160.84990;-39.93210;,
 42.30090;124.64990;-39.93210;,
 89.50090;124.64990;-39.93210;,
 42.30090;160.84990;-39.93210;,
 42.30090;160.84990;-90.63210;,
 42.30090;124.64990;-90.63210;,
 42.30090;124.64990;-39.93210;,
 89.50090;160.84990;-90.63210;,
 42.30090;160.84990;-90.63210;,
 42.30090;124.64990;-90.63210;,
 89.50090;124.64990;-90.63210;,
 -84.41380;115.26080;-100.00000;,
 -79.40160;107.99380;-100.00000;,
 -79.40160;29.25390;-100.00000;,
 -84.41380;29.25390;-100.00000;,
 -96.35520;115.26080;-100.00000;,
 -96.35520;29.25390;-100.00000;,
 -100.00000;29.25390;-100.00000;,
 -100.00000;126.77720;-100.00000;,
 -79.40160;20.71390;-150.84750;,
 -79.40160;-0.22280;-150.84750;,
 -100.00000;-0.22280;-150.84750;,
 -100.00000;20.71390;-150.84750;,
 -79.40160;20.71390;-150.84750;,
 -100.00000;20.71390;-150.84750;,
 -100.00000;29.25390;-150.84750;,
 -79.40160;29.25390;-150.84750;,
 -100.00000;-0.22280;-100.00000;,
 -100.00000;20.71390;-100.00000;,
 -100.00000;20.71390;-150.84750;,
 -100.00000;-0.22280;-150.84750;,
 -100.00000;29.25390;-100.00000;,
 -100.00000;20.71390;-100.00000;,
 100.00000;29.25390;-100.00000;,
 100.00000;107.99380;-100.00000;,
 100.00000;107.99380;-75.40230;,
 100.00000;29.25390;-75.40230;,
 100.00000;29.25390;-75.40230;,
 100.00000;107.99380;-75.40230;,
 100.00000;107.99380;80.51570;,
 100.00000;29.25390;80.51570;,
 100.00000;107.99380;-75.40230;,
 100.00000;115.26080;-100.00000;,
 100.00000;115.26080;80.51570;,
 100.00000;126.77720;-100.00000;,
 100.00000;126.77720;100.00000;,
 -100.00000;-0.22280;-100.00000;,
 -100.00000;-0.22280;118.15950;,
 -100.00000;20.71390;118.15950;,
 -100.00000;20.71390;-100.00000;,
 -100.00000;20.71390;118.15950;,
 -100.00000;29.25390;100.00000;,
 -100.00000;29.25390;-100.00000;,
 -100.00000;29.25390;100.00000;,
 -100.00000;126.77720;100.00000;,
 -100.00000;126.77720;-100.00000;,
 111.19860;20.71390;80.51570;,
 111.19860;29.25390;80.51570;,
 111.19860;29.25390;100.00000;,
 111.19860;20.71390;100.00000;,
 111.19860;20.71390;80.51570;,
 111.19860;20.71390;100.00000;,
 111.19860;-0.22280;100.00000;,
 111.19860;-0.22280;80.51570;,
 111.19860;20.71390;-115.96500;,
 111.19860;20.71390;-100.00000;,
 111.19860;-0.22280;-100.00000;,
 111.19860;-0.22280;-115.96500;,
 111.19860;-0.22280;-150.84750;,
 111.19860;20.71390;-150.84750;,
 111.19860;20.71390;-115.96500;,
 111.19860;20.71390;-150.84750;,
 111.19860;29.25390;-150.84750;,
 111.19860;29.25390;-115.96500;,
 111.19860;29.25390;-100.00000;,
 111.19860;20.71390;-100.00000;,
 111.19860;20.71390;-82.27030;,
 111.19860;20.71390;-75.40230;,
 111.19860;-0.22280;-75.40230;,
 111.19860;-0.22280;-82.27030;,
 111.19860;-0.22280;-100.00000;,
 111.19860;20.71390;-100.00000;,
 111.19860;20.71390;-82.27030;,
 111.19860;29.25390;-82.27030;,
 111.19860;29.25390;-75.40230;,
 111.19860;20.71390;-75.40230;,
 111.19860;20.71390;-60.93850;,
 111.19860;-0.22280;-60.93850;,
 111.19860;20.71390;-60.93850;,
 111.19860;29.25390;-60.93850;,
 -79.40160;20.71390;118.15950;,
 -100.00000;20.71390;118.15950;,
 -100.00000;-0.22280;118.15950;,
 -79.40160;-0.22280;118.15950;,
 93.88360;29.25390;118.15950;,
 93.88360;20.71390;118.15950;,
 93.88360;20.71390;118.15950;,
 93.88360;-0.22280;118.15950;,
 54.44710;29.25390;118.15950;,
 54.44710;20.71390;118.15950;,
 93.88360;20.71390;118.15950;,
 54.44710;20.71390;118.15950;,
 54.44710;-0.22280;118.15950;,
 93.88360;-0.22280;118.15950;,
 100.00000;115.26080;-100.00000;,
 100.00000;107.99380;-100.00000;,
 54.44710;107.99380;-100.00000;,
 54.44710;115.26080;-100.00000;,
 100.00000;29.25390;-100.00000;,
 54.44710;29.25390;-100.00000;,
 111.19860;-0.22280;-150.84750;,
 54.44710;-0.22280;-150.84750;,
 54.44710;20.71390;-150.84750;,
 111.19860;20.71390;-150.84750;,
 54.44710;20.71390;-150.84750;,
 -11.52900;29.25390;-150.84750;,
 100.00000;29.25390;110.69000;,
 -100.00000;23.08730;-150.84750;,
 -51.20620;23.08730;-150.84750;,
 -79.40160;29.25390;-150.84750;,
 -100.00000;29.25390;-150.84750;,
 -51.20620;23.08730;-100.00000;,
 -100.00000;23.08730;-100.00000;,
 -100.00000;23.08730;-100.00000;,
 -100.00000;23.08730;-150.84750;,
 -100.00000;29.25390;-150.84750;,
 111.19860;23.08730;80.51570;,
 111.19860;23.08730;100.00000;,
 111.19860;29.25390;100.00000;,
 111.19860;29.25390;80.51570;,
 100.00000;23.08730;80.51570;,
 100.00000;23.08730;100.00000;,
 111.19860;23.08730;-150.84750;,
 111.19860;23.08730;-115.96500;,
 111.19860;29.25390;-115.96500;,
 111.19860;29.25390;-150.84750;,
 111.19860;23.08730;-100.00000;,
 111.19860;29.25390;-100.00000;,
 111.19860;23.08730;-82.27030;,
 111.19860;29.25390;-82.27030;,
 111.19860;23.08730;-75.40230;,
 111.19860;29.25390;-75.40230;,
 111.71810;23.08730;-60.93850;,
 111.19860;29.25390;-60.93850;,
 100.00000;23.08730;-100.00000;,
 100.00000;29.25390;-75.40230;,
 100.00000;29.25390;80.51570;,
 -100.00000;23.08730;118.15950;,
 -100.00000;23.08730;100.00000;,
 -100.00000;29.25390;100.00000;,
 -100.00000;29.25390;118.15950;,
 100.00000;23.08730;-100.00000;,
 -11.52900;23.08730;-100.00000;,
 -11.52900;23.08730;-150.84750;,
 111.19860;23.08730;-150.84750;,
 111.19860;29.25390;-150.84750;,
 -11.52900;29.25390;-150.84750;,
 100.00000;23.08730;110.69000;,
 93.88360;23.08730;118.15950;,
 93.88360;29.25390;118.15950;,
 100.00000;29.25390;110.69000;,
 100.00000;23.08730;100.00000;,
 -51.20620;29.25390;-150.84750;,
 -51.20620;20.71390;-150.84750;,
 -51.20620;20.71390;-150.84750;,
 -51.20620;-0.22280;-150.84750;,
 -79.40160;-0.22280;-150.84750;,
 -79.40160;20.71390;-150.84750;,
 100.00000;126.77720;-100.00000;,
 -100.00000;126.77720;-100.00000;,
 -100.00000;126.77720;100.00000;,
 100.00000;126.77720;100.00000;,
 54.44710;-0.22280;118.15950;,
 54.44710;20.71390;118.15950;,
 -79.40160;20.71390;118.15950;,
 -79.40160;-0.22280;118.15950;,
 -100.00000;29.25390;118.15950;,
 -79.40160;20.71390;118.15950;,
 100.00000;126.77720;100.00000;,
 -100.00000;126.77720;100.00000;,
 -100.00000;29.25390;100.00000;,
 100.00000;23.08730;100.00000;,
 54.44710;29.25390;118.15950;,
 93.88360;23.08730;118.15950;,
 -100.00000;23.08730;118.15950;,
 -100.00000;29.25390;118.15950;,
 100.00000;23.08730;100.00000;,
 -100.00000;23.08730;100.00000;,
 -11.52900;23.08730;-150.84750;,
 -51.20620;23.08730;-150.84750;,
 -51.20620;23.08730;-100.00000;,
 -11.52900;23.08730;-100.00000;,
 -11.52900;20.71390;-150.84750;,
 -11.52900;-0.22280;-150.84750;,
 -79.40160;29.25390;-100.00000;,
 -79.40160;107.99380;-100.00000;,
 54.44710;107.99380;-100.00000;,
 54.44710;29.25390;-100.00000;,
 -79.40160;107.99380;-100.00000;,
 -79.40160;115.26080;-100.00000;,
 100.00000;115.26080;-100.00000;,
 100.00000;29.25390;-100.00000;,
 -51.20620;23.08730;-100.00000;,
 -100.00000;23.08730;-100.00000;,
 -84.41380;115.26080;-100.00000;,
 -79.40160;115.26080;-100.00000;,
 -100.00000;126.77720;-100.00000;,
 -84.41380;115.26080;-100.00000;,
 -100.00000;126.77720;-100.00000;,
 -96.35520;115.26080;-100.00000;,
 93.88360;23.08730;118.15950;,
 54.44710;29.25390;118.15950;,
 -100.00000;29.25390;100.00000;,
 100.00000;126.77720;100.00000;,
 111.19860;23.08730;-150.84750;,
 100.00000;126.77720;-100.00000;,
 100.00000;126.77720;-100.00000;,
 -51.20620;23.08730;-150.84750;,
 -51.20620;29.25390;-150.84750;,
 -79.40160;29.25390;-150.84750;,
 -11.52900;20.71390;-150.84750;,
 -11.52900;23.08730;-100.00000;,
 -79.40160;29.25390;-100.00000;,
 -79.40160;29.25390;-100.00000;,
 -79.40160;115.26080;-100.00000;,
 -100.00000;126.77720;-100.00000;,
 100.00000;126.77720;-100.00000;,
 -8.29290;29.15280;-237.19150;,
 -8.29290;29.15280;-150.67889;,
 -8.29290;19.65280;-150.67889;,
 -8.29290;19.65280;-237.19150;,
 -54.79290;29.15280;-150.67889;,
 -54.79290;29.15280;-237.19150;,
 -54.79290;19.65280;-237.19150;,
 -54.79290;19.65280;-150.67889;,
 -51.33330;29.15280;-237.19150;,
 -54.79290;29.15280;-237.19150;,
 -54.79290;29.15280;-150.67889;,
 -51.33330;29.15280;-150.67889;,
 -51.33330;19.65280;-237.19150;,
 -51.33330;19.65280;-150.67889;,
 -54.79290;19.65280;-150.67889;,
 -54.79290;19.65280;-237.19150;,
 -51.33330;29.15280;-150.67889;,
 -54.79290;29.15280;-150.67889;,
 -54.79290;19.65280;-150.67889;,
 -51.33330;19.65280;-150.67889;,
 -11.52360;29.15280;-237.19150;,
 -11.52360;29.15280;-150.67889;,
 -8.29290;29.15280;-150.67889;,
 -8.29290;29.15280;-237.19150;,
 -11.52360;19.65280;-237.19150;,
 -8.29290;19.65280;-237.19150;,
 -8.29290;19.65280;-150.67889;,
 -11.52360;19.65280;-150.67889;,
 -11.52360;29.15280;-150.67889;,
 -11.52360;19.65280;-150.67889;,
 -8.29290;19.65280;-150.67889;,
 -8.29290;29.15280;-150.67889;,
 -51.33330;22.79670;-150.67889;,
 -51.33330;22.79670;-237.19150;,
 -11.52360;22.79670;-237.19150;,
 -11.52360;22.79670;-150.67889;,
 -51.33330;-3.27290;-278.02280;,
 -51.33330;6.22710;-278.02280;,
 -51.33330;29.15280;-237.19150;,
 -51.33330;19.65280;-237.19150;,
 -54.79290;-3.27290;-278.02280;,
 -54.79290;19.65280;-237.19150;,
 -54.79290;6.22710;-278.02280;,
 -54.79290;-3.27290;-278.02280;,
 -54.79290;19.65280;-237.19150;,
 -54.79290;29.15280;-237.19150;,
 -54.79290;6.22710;-278.02280;,
 -54.79290;29.15280;-237.19150;,
 -8.29290;6.22710;-278.02280;,
 -11.52360;6.22710;-278.02280;,
 -11.52360;29.15280;-237.19150;,
 -8.29290;29.15280;-237.19150;,
 -8.29290;-3.27290;-278.02280;,
 -8.29290;6.22710;-278.02280;,
 -8.29290;29.15280;-237.19150;,
 -8.29290;19.65280;-237.19150;,
 -11.52360;-3.27290;-278.02280;,
 -8.29290;-3.27290;-278.02280;,
 -8.29290;19.65280;-237.19150;,
 -11.52360;19.65280;-237.19150;,
 -11.52360;-3.27290;-278.02280;,
 -11.52360;-0.12900;-278.02280;,
 -11.52360;22.79670;-237.19150;,
 -11.52360;19.65280;-237.19150;,
 -51.33330;-3.27290;-278.02280;,
 -51.33330;19.65280;-237.19150;,
 -51.33330;-0.12900;-278.02280;,
 -51.33330;22.79670;-237.19150;;
 
 132;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;16,9,20,21;,
 4;22,23,10,19;,
 4;24,25,26,27;,
 4;28,24,27,29;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;44,38,37,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;54,55,56,0;,
 4;55,57,58,56;,
 4;59,60,61,62;,
 4;45,63,64,44;,
 4;65,66,67,68;,
 4;69,70,71,72;,
 4;73,74,75,76;,
 4;77,78,79,80;,
 4;77,80,81,82;,
 4;83,84,85,86;,
 4;83,86,87,88;,
 4;89,90,91,92;,
 4;89,92,93,94;,
 4;95,88,87,96;,
 4;95,96,97,98;,
 4;99,73,76,100;,
 4;99,100,91,90;,
 4;101,98,97,102;,
 4;101,102,70,69;,
 4;103,104,105,106;,
 4;71,107,108,72;,
 4;74,109,110,75;,
 4;107,111,112,108;,
 4;113,114,115,116;,
 4;117,118,119,120;,
 4;118,121,122,119;,
 4;123,124,125,126;,
 4;85,84,127,128;,
 3;107,71,129;,
 4;130,131,132,133;,
 4;134,131,130,135;,
 4;134,135,29,27;,
 4;136,137,138,30;,
 4;139,140,141,142;,
 4;140,139,143,144;,
 4;145,146,147,148;,
 4;146,149,150,147;,
 4;149,151,152,150;,
 4;151,153,154,152;,
 4;153,155,156,154;,
 4;155,139,142,156;,
 4;143,157,158,159;,
 4;139,155,157,143;,
 4;160,161,162,163;,
 4;164,165,122,121;,
 4;166,167,168,169;,
 4;164,167,166,165;,
 4;170,171,172,173;,
 3;171,170,174;,
 4;140,170,173,141;,
 3;140,144,170;,
 4;175,176,36,39;,
 4;177,178,179,180;,
 4;181,182,183,184;,
 4;185,186,187,188;,
 4;112,111,189,190;,
 4;191,192,193,194;,
 4;195,196,197,198;,
 4;196,199,200,197;,
 4;201,202,203,204;,
 4;205,125,124,206;,
 4;205,206,178,177;,
 4;207,208,209,210;,
 4;211,212,120,119;,
 3;213,48,47;,
 3;157,155,153;,
 3;157,151,149;,
 3;157,214,158;,
 3;157,153,151;,
 3;157,149,146;,
 3;215,27,26;,
 3;216,30,29;,
 3;217,218,25;,
 3;63,189,64;,
 3;219,218,220;,
 3;221,220,222;,
 3;189,63,190;,
 3;223,224,172;,
 3;144,143,159;,
 3;199,225,200;,
 3;226,0,56;,
 3;227,157,146;,
 3;228,117,120;,
 3;229,120,212;,
 3;230,231,232;,
 3;128,127,233;,
 3;234,235,122;,
 3;236,204,203;,
 3;237,238,239;,
 4;240,241,242,243;,
 4;244,245,246,247;,
 4;248,249,250,251;,
 4;252,253,254,255;,
 4;256,257,258,259;,
 4;260,261,262,263;,
 4;264,265,266,267;,
 4;264,267,253,252;,
 4;268,269,270,271;,
 4;272,273,248,251;,
 4;274,275,261,260;,
 4;274,273,272,275;,
 4;276,277,278,279;,
 4;280,276,279,281;,
 4;282,283,284,285;,
 4;277,286,287,278;,
 4;277,276,280,286;,
 4;288,289,290,291;,
 4;292,293,294,295;,
 4;296,297,298,299;,
 4;289,296,299,290;,
 4;289,288,297,296;,
 4;300,301,302,303;,
 4;304,300,303,305;,
 4;306,304,305,307;,
 4;301,306,307,302;,
 4;301,300,304,306;;
 
 MeshMaterialList {
  8;
  132;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  3,
  2,
  2,
  4,
  2,
  4,
  2,
  1,
  3,
  2,
  2,
  4,
  2,
  4,
  5,
  5,
  2,
  4,
  4,
  5,
  2,
  4,
  4,
  2,
  5,
  4,
  4,
  2,
  4,
  5,
  4,
  2,
  3,
  2,
  2,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  5,
  2,
  5,
  4,
  2,
  2,
  2,
  2,
  5,
  5,
  0,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  2,
  2,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  4,
  2,
  2,
  2,
  4,
  4,
  7,
  5,
  5,
  7,
  5,
  5,
  5,
  7,
  7,
  7,
  7,
  5,
  6,
  7,
  7,
  7,
  6,
  5,
  7,
  7,
  5,
  5,
  5,
  7,
  7;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\tex_esta_01.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\tex_esta_01.png";
   }
  }
  Material {
   0.731200;0.731200;0.731200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.564800;0.298400;0.112800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\tex_esta_02.png";
   }
  }
  Material {
   0.213600;0.213600;0.213600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "TEXTURE\\tex_esta_02.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.393651;0.000000;0.919260;,
  0.000000;1.000000;0.000000;,
  0.928368;0.000000;0.371662;,
  0.928368;0.000000;0.371662;,
  0.000000;1.000000;0.000000;,
  -0.999739;-0.021001;0.008954;,
  -0.999779;-0.021010;-0.000916;,
  -0.999085;-0.042002;0.008036;,
  -0.733472;0.000000;-0.679719;,
  -0.919372;0.000000;-0.393389;,
  -0.281875;0.000000;-0.959451;,
  0.000000;-1.000000;-0.000000;,
  -0.428049;0.000000;-0.903755;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.967460;-0.253024;,
  0.000000;-0.967460;0.253024;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.967460;-0.253024;,
  0.000000;-0.967460;0.253024;,
  0.000000;-0.871958;0.489581;,
  0.000000;0.871958;-0.489581;,
  0.000000;-0.871958;0.489581;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.967460;0.253024;,
  0.000000;0.967460;-0.253024;,
  0.000000;-0.871958;0.489581;,
  0.000000;0.871958;-0.489581;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.871958;0.489581;,
  0.000000;0.871958;-0.489581;;
  132;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;8,8,8,8;,
  4;15,15,15,15;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;1,1,6,7;,
  4;1,7,6,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;6,4,4,7;,
  4;7,4,4,6;,
  4;4,2,2,4;,
  4;4,2,2,4;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;5,5,5;,
  4;2,2,2,2;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;10,13,13,10;,
  4;8,8,8,8;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,9,9,3;,
  4;9,11,11,9;,
  4;11,10,10,11;,
  4;1,1,1,1;,
  4;8,8,8,8;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;8,8,8,8;,
  4;12,14,16,12;,
  3;8,8,8;,
  4;13,12,12,13;,
  3;8,8,8;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;8,8,8,8;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,14,0,0;,
  4;8,8,8,8;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  3;1,1,1;,
  3;8,8,8;,
  3;8,8,8;,
  3;1,1,1;,
  3;8,8,8;,
  3;8,8,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;3,3,3;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,2,2;,
  3;14,0,16;,
  3;1,1,1;,
  3;2,2,2;,
  3;1,1,1;,
  3;8,8,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;2,2,2;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;19,19,21,21;,
  4;20,22,22,20;,
  4;28,28,28,28;,
  4;23,21,21,23;,
  4;24,29,22,22;,
  4;24,22,22,20;,
  4;28,28,28,28;,
  4;18,18,18,18;,
  4;17,17,17,17;,
  4;30,30,21,21;,
  4;18,18,18,18;,
  4;25,31,20,20;,
  4;17,17,17,17;,
  4;32,32,19,19;,
  4;33,33,33,33;,
  4;26,26,23,23;,
  4;18,18,18,18;,
  4;27,34,29,24;,
  4;17,17,17,17;,
  4;33,33,33,33;,
  4;18,18,18,18;,
  4;31,27,24,20;,
  4;17,17,17,17;,
  4;35,35,30,30;,
  4;33,33,33,33;;
 }
 MeshTextureCoords {
  308;
  0.902580;0.147900;,
  1.000000;0.147900;,
  1.000000;0.767900;,
  0.902580;0.767900;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.077930;0.147900;,
  0.102990;0.147900;,
  0.102990;0.767900;,
  0.077930;0.767900;,
  0.018220;0.147900;,
  0.018220;0.767900;,
  0.000000;0.767900;,
  0.000000;0.147900;,
  0.077930;0.835140;,
  0.077930;1.000000;,
  0.018220;1.000000;,
  0.018220;0.835140;,
  -3.576895;-1.157908;,
  -4.634524;-1.157908;,
  -4.634524;-1.841436;,
  -3.576895;-1.841436;,
  0.000000;1.000000;,
  0.000000;0.835140;,
  0.000000;0.835140;,
  0.000000;1.000000;,
  -4.634524;-1.841436;,
  -4.634524;-1.157908;,
  0.088650;0.767900;,
  0.088650;0.147900;,
  0.122990;0.147900;,
  0.122990;0.767900;,
  6.806524;0.146579;,
  6.806524;-0.719189;,
  -5.988323;-0.719189;,
  -5.988323;0.146579;,
  0.195310;0.147900;,
  0.195310;0.090680;,
  0.902580;0.090680;,
  0.195310;0.000000;,
  0.902580;0.000000;,
  0.804690;1.000000;,
  0.097420;1.000000;,
  0.097420;0.835140;,
  0.804690;0.835140;,
  -4.634524;-1.157908;,
  -4.634524;-1.841436;,
  0.804690;0.767900;,
  0.097420;0.767900;,
  0.097420;0.147900;,
  0.804690;0.147900;,
  6.209519;-1.157908;,
  6.209519;-1.841436;,
  6.209519;-1.841436;,
  6.209519;-1.157908;,
  0.902580;0.835140;,
  1.000000;0.835140;,
  1.000000;1.000000;,
  0.902580;1.000000;,
  1.000000;0.835140;,
  1.000000;0.835140;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.835140;,
  6.209519;-1.157908;,
  6.209519;-1.157908;,
  6.209519;-1.841436;,
  6.209519;-1.841436;,
  6.209519;-1.841436;,
  6.209519;-1.157908;,
  0.088650;0.835140;,
  0.122990;0.835140;,
  0.122990;1.000000;,
  0.088650;1.000000;,
  0.000000;1.000000;,
  0.000000;0.835140;,
  6.209519;-1.157908;,
  6.209519;-1.841436;,
  6.209519;-1.841436;,
  6.209519;-1.157908;,
  0.195310;0.835140;,
  0.195310;1.000000;,
  6.209519;-1.157908;,
  6.209519;-1.841436;,
  0.922070;0.835140;,
  0.981780;0.835140;,
  0.981780;1.000000;,
  0.922070;1.000000;,
  5.320476;-1.841436;,
  5.320476;-1.157908;,
  1.000000;0.835140;,
  1.000000;1.000000;,
  3.295600;-1.841436;,
  3.295600;-1.157908;,
  0.030580;0.835140;,
  0.227760;0.835140;,
  0.227760;1.000000;,
  0.030580;1.000000;,
  0.969420;0.090680;,
  0.969420;0.147900;,
  0.772240;0.147900;,
  0.772240;0.090680;,
  0.969420;0.767900;,
  0.772240;0.767900;,
  0.969420;1.000000;,
  0.772240;1.000000;,
  0.772240;0.835140;,
  0.969420;0.835140;,
  3.295600;-1.157908;,
  -0.091959;-1.841436;,
  5.634524;-1.841436;,
  0.018220;0.767900;,
  0.077930;0.767900;,
  0.077930;0.767900;,
  0.018220;0.767900;,
  0.077930;0.767900;,
  0.018220;0.767900;,
  0.000000;0.767900;,
  0.000000;0.767900;,
  0.000000;0.767900;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  5.634770;-1.841450;,
  5.634770;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  6.209790;-1.841450;,
  5.634770;-1.841450;,
  5.634770;-1.841450;,
  5.634770;-1.841450;,
  -4.634770;-1.841450;,
  -4.634770;-1.841450;,
  -4.634770;-1.841450;,
  -4.634770;-1.841450;,
  0.969420;0.767900;,
  0.772240;0.767900;,
  0.772240;0.767900;,
  0.969420;0.767900;,
  0.969420;0.767900;,
  0.772240;0.767900;,
  5.634770;-1.841450;,
  5.320710;-1.841450;,
  5.320710;-1.841450;,
  5.634770;-1.841450;,
  5.320710;-1.841450;,
  -2.129195;-1.841436;,
  -2.129195;-1.157908;,
  0.243970;0.835140;,
  0.243970;1.000000;,
  0.102990;1.000000;,
  0.102990;0.835140;,
  0.243970;0.804690;,
  0.102990;0.804690;,
  0.102990;0.097420;,
  0.243970;0.097420;,
  0.756030;1.000000;,
  0.756030;0.835140;,
  0.897010;0.835140;,
  0.897010;1.000000;,
  -4.634524;-1.841436;,
  -3.576895;-1.157908;,
  0.756030;0.147900;,
  0.897010;0.147900;,
  0.897010;0.767900;,
  0.756030;0.767900;,
  -2.129320;-1.841450;,
  -2.129320;-1.841450;,
  -3.577090;-1.841450;,
  -3.577090;-1.841450;,
  -2.129320;-1.841450;,
  -3.577090;-1.841450;,
  0.442360;0.767900;,
  0.243970;0.767900;,
  0.243970;0.767900;,
  0.442360;0.767900;,
  0.442360;0.835140;,
  0.442360;1.000000;,
  -5.976252;0.146579;,
  -5.976252;-0.719189;,
  5.007558;-0.719189;,
  5.007558;0.146579;,
  0.442360;0.147900;,
  0.442360;0.090680;,
  0.105820;0.090680;,
  5.634770;-1.841450;,
  0.090460;0.767900;,
  0.009110;0.767900;,
  0.077930;0.119290;,
  0.102990;0.090680;,
  0.090460;0.000000;,
  0.077930;0.090680;,
  0.048080;0.000000;,
  0.018220;0.090680;,
  4.308220;-1.841450;,
  3.295730;-1.841450;,
  -3.577090;-1.841450;,
  1.000000;0.119290;,
  5.922280;-1.841450;,
  0.870830;0.000000;,
  0.607300;0.000000;,
  0.173480;0.767900;,
  0.243970;0.767900;,
  0.102990;0.767900;,
  -0.091959;-1.157908;,
  0.607300;0.767900;,
  0.442360;0.767900;,
  0.343170;0.767900;,
  0.173480;0.090680;,
  0.102990;0.000000;,
  0.243970;0.000000;,
  0.074199;-1.833344;,
  0.074199;-1.833344;,
  0.074199;-1.072979;,
  0.074199;-1.072979;,
  -2.313355;-1.833344;,
  -2.313355;-1.833344;,
  -2.313355;-1.072979;,
  -2.313355;-1.072979;,
  0.074400;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.074400;0.000000;,
  0.074400;0.000000;,
  0.074400;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.925600;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.925600;1.000000;,
  0.930520;1.000000;,
  0.930520;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.930520;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.930520;1.000000;,
  0.069480;0.000000;,
  0.069480;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.074400;0.000000;,
  0.074400;1.000000;,
  0.930520;1.000000;,
  0.930520;0.000000;,
  0.074400;1.000000;,
  0.074400;0.000000;,
  0.074400;0.000000;,
  0.074400;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  -2.324376;4.144110;,
  -2.324376;4.841333;,
  -2.324376;4.888910;,
  -2.324376;4.191687;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.930520;0.000000;,
  0.930520;0.000000;,
  1.000000;0.000000;,
  0.072531;4.841333;,
  0.072531;4.144110;,
  0.072531;4.191687;,
  0.072531;4.888910;,
  0.930520;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.930520;1.000000;,
  -0.406090;0.250730;,
  -0.406090;0.216160;,
  -0.406090;0.216160;,
  -0.406090;0.250730;,
  -3.672930;0.250730;,
  -3.672930;0.250730;,
  -3.672930;0.216160;,
  -3.672930;0.216160;;
 }
}
