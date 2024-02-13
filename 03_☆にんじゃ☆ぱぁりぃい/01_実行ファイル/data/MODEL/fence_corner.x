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
 68;
 -450.00000;125.00000;-35.00000;,
 30.00032;125.00000;-30.00000;,
 64.99998;0.00000;-64.99976;,
 -450.00000;0.00000;-65.00000;,
 -34.99968;125.00000;35.00000;,
 -450.00000;125.00000;35.00000;,
 -450.00000;0.00000;65.00000;,
 -64.99968;0.00000;65.00000;,
 -450.00000;125.00000;35.00000;,
 -450.00000;125.00000;-35.00000;,
 -450.00000;0.00000;-65.00000;,
 -450.00000;0.00000;65.00000;,
 -450.00000;0.00000;-65.00000;,
 64.99998;0.00000;-64.99976;,
 -64.99968;0.00000;65.00000;,
 -24.99968;205.19884;25.00000;,
 -450.00000;205.19884;25.00000;,
 -34.99968;125.00000;35.00000;,
 -450.00000;205.19884;-25.00000;,
 25.00032;205.19884;-25.00000;,
 30.00032;125.00000;-30.00000;,
 -450.00000;125.00000;-35.00000;,
 -50.89120;207.59084;50.89146;,
 -450.00000;207.59084;51.78269;,
 -450.00000;207.59084;-51.78269;,
 51.78268;207.59084;-51.49979;,
 -12.49968;244.78000;12.50000;,
 -450.00000;244.78000;12.50000;,
 -450.00000;244.78000;-12.50000;,
 12.50032;244.78000;-12.50000;,
 -12.49968;257.95190;12.50000;,
 -450.00000;257.95190;12.50000;,
 -450.00000;257.95190;-12.50000;,
 12.00032;257.95190;-12.50000;,
 -35.00000;125.00000;450.00000;,
 -34.99968;125.00000;35.00000;,
 -64.99968;0.00000;65.00000;,
 -65.00002;0.00000;450.00000;,
 30.00032;125.00000;-30.00000;,
 34.99998;125.00000;450.00000;,
 64.99997;0.00000;450.00000;,
 64.99998;0.00000;-64.99976;,
 34.99998;125.00000;450.00000;,
 -35.00000;125.00000;450.00000;,
 -65.00002;0.00000;450.00000;,
 64.99997;0.00000;450.00000;,
 -65.00002;0.00000;450.00000;,
 -64.99968;0.00000;65.00000;,
 64.99998;0.00000;-64.99976;,
 25.00032;205.19884;-25.00000;,
 25.00001;205.19884;450.00000;,
 30.00032;125.00000;-30.00000;,
 -25.00001;205.19884;450.00000;,
 -24.99968;205.19884;25.00000;,
 -34.99968;125.00000;35.00000;,
 -35.00000;125.00000;450.00000;,
 51.78268;207.59084;-51.49979;,
 51.78269;207.59084;450.00000;,
 -51.78270;207.59084;450.00000;,
 -50.89120;207.59084;50.89146;,
 12.50032;244.78000;-12.50000;,
 12.49999;244.78000;450.00000;,
 -12.50002;244.78000;450.00000;,
 -12.49968;244.78000;12.50000;,
 12.00032;257.95190;-12.50000;,
 12.49999;257.95190;450.00000;,
 -12.50002;257.95190;450.00000;,
 -12.49968;257.95190;12.50000;;
 
 34;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,11;,
 4;15,16,8,17;,
 4;18,19,20,21;,
 4;16,18,21,8;,
 4;22,23,16,15;,
 4;24,25,19,18;,
 4;23,24,18,16;,
 4;26,27,23,22;,
 4;28,29,25,24;,
 4;27,28,24,23;,
 4;30,31,27,26;,
 4;32,33,29,28;,
 4;31,32,28,27;,
 4;31,30,33,32;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,45;,
 4;49,50,42,51;,
 4;52,53,54,55;,
 4;50,52,55,42;,
 4;56,57,50,49;,
 4;58,59,53,52;,
 4;57,58,52,50;,
 4;60,61,57,56;,
 4;62,63,59,58;,
 4;61,62,58,57;,
 4;64,65,61,60;,
 4;66,67,63,62;,
 4;65,66,62,61;,
 4;65,64,67,66;;
 
 MeshMaterialList {
  5;
  34;
  0,
  0,
  4,
  4,
  2,
  2,
  4,
  3,
  3,
  4,
  3,
  3,
  4,
  3,
  3,
  4,
  3,
  1,
  1,
  4,
  4,
  2,
  2,
  4,
  3,
  3,
  4,
  3,
  3,
  4,
  3,
  3,
  4,
  3;;
  Material {
   0.392157;0.392157;0.392157;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\field000.jpg";
   }
  }
  Material {
   0.392157;0.392157;0.392157;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\field000.jpg";
   }
  }
  Material {
   0.674510;0.674510;0.674510;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.454902;0.454902;0.454902;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  35;
  0.005149;0.173002;-0.984908;,
  0.005065;0.251542;-0.967833;,
  0.000000;0.178830;0.983880;,
  0.000000;0.233373;0.972387;,
  0.005200;0.093344;-0.995620;,
  0.000000;0.123732;0.992316;,
  0.000025;-0.995996;-0.089403;,
  0.044580;-0.998001;-0.044791;,
  -0.045281;-0.997947;0.045281;,
  0.000099;-0.995899;0.090476;,
  0.000106;0.394526;-0.918885;,
  0.000417;0.392656;0.919685;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -0.983880;0.178830;-0.000001;,
  -0.972387;0.233373;-0.000001;,
  0.984908;0.173002;-0.005149;,
  0.967833;0.251542;-0.005065;,
  -0.992316;0.123732;-0.000001;,
  0.995620;0.093344;-0.005200;,
  -0.090476;-0.995899;-0.000099;,
  0.088958;-0.996035;0.000000;,
  -0.919685;0.392656;-0.000418;,
  0.914766;0.403984;-0.000293;,
  -1.000000;0.000000;-0.000001;,
  0.999820;0.018970;-0.000540;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000768;0.722240;0.691642;,
  -0.396169;0.828311;0.396169;,
  0.393555;0.830526;-0.394133;,
  0.000194;0.725049;-0.688698;,
  0.000000;1.000000;0.000000;,
  0.687493;0.726191;0.000000;,
  -0.691642;0.722240;-0.000768;;
  34;
  4;0,0,1,1;,
  4;2,2,3,3;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;5,5,2,2;,
  4;4,4,0,0;,
  4;26,26,26,26;,
  4;8,9,9,8;,
  4;6,7,7,6;,
  4;26,26,26,26;,
  4;11,11,28,29;,
  4;10,10,30,31;,
  4;26,26,26,26;,
  4;13,13,11,11;,
  4;12,12,10,10;,
  4;26,26,26,26;,
  4;32,32,32,32;,
  4;14,14,15,15;,
  4;16,16,17,17;,
  4;13,13,13,13;,
  4;27,27,27,27;,
  4;19,19,16,16;,
  4;18,18,14,14;,
  4;13,13,13,13;,
  4;7,21,21,7;,
  4;20,8,8,20;,
  4;13,13,13,13;,
  4;23,23,33,30;,
  4;22,22,29,34;,
  4;13,13,13,13;,
  4;25,25,23,23;,
  4;24,24,22,22;,
  4;13,13,13,13;,
  4;32,32,32,32;;
 }
 MeshTextureCoords {
  68;
  -0.750438;0.074774;,
  1.649564;0.074774;,
  1.824562;0.699774;,
  -0.750438;0.699774;,
  1.324564;0.074774;,
  -0.750438;0.074774;,
  -0.750438;0.699774;,
  1.174564;0.699774;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  -1.750000;0.074774;,
  0.325000;0.074774;,
  0.175000;0.699774;,
  -1.750000;0.699774;,
  0.650000;0.074774;,
  -1.750000;0.074774;,
  -1.750000;0.699774;,
  0.824999;0.699774;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;;
 }
}
