float dot(float a[16], float b[16]) {
  float acc = 0.0f;
  for (int i = 0; i < 16; i++) {
#pragma HLS pipeline II = 1
    float x = a[i] * b[i];
    acc += x;
  }
  return acc;
}
