float4 vsmain( float4 pos : POSITION ) : SV_POSITION
{
        return pos;
}

 float4 psmain( float4 pos : SV_POSITION ) : SV_Target
 {
        return float4(0.6f,0.9f, 0.6f, 0.9f );   
 }