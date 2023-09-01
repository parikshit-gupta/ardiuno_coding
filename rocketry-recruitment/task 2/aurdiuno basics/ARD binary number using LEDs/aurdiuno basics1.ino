int arr[3]={12,8,7};
int i=0;
int arr_bin[3]={1,0,1};

void setup()
{
  for(i=0;i<3;i++)
  {
    pinMode(arr[i], OUTPUT);
  }
}

void loop(){
  for (i=0;i<3;i++)
  {
    digitalWrite(arr[i],arr_bin[i]);
  }
  delay(500);
}