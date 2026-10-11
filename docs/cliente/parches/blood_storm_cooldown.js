const fs=require("fs");
const src="C:/Users/Meinmundy/Downloads/Mu-S8 v3/Data/Local/Eng/skill_eng.bmd";
const b=Buffer.from(fs.readFileSync(src));
const S=108,N=650,DATA=S*N,KEY=0x5A18;
function checksum(buf,size,wKey){
  let res=((wKey<<9)>>>0);
  for(let c=0;c<=size-4;c+=4){
    const t=buf.readUInt32LE(c);
    if(((c/4+wKey)%2)===0) res=(res^t)>>>0; else res=(res+t)>>>0;
    if(c%16===0){ const dk=wKey; res=(res ^ ((dk+res)>>>((c/4)%8+1)))>>>0; }
  }
  return res>>>0;
}
const stored=b.readUInt32LE(DATA);
const calc=checksum(b,DATA,KEY);
console.log("stored",stored,"calc",calc,"match",stored===calc);

const key3=[0xFC,0xCF,0xAB];
const recIdx={344:5000,346:3000};
const out=Buffer.from(b);
for(const [num,ms] of Object.entries(recIdx)){
  const i=+num, o=i*S;
  const r=Buffer.from(out.subarray(o,o+S));
  for(let j=0;j<S;j++) r[j]^=key3[j%3];
  const before=r.readInt32LE(64);
  r.writeInt32LE(ms,64);
  for(let j=0;j<S;j++) r[j]^=key3[j%3];
  r.copy(out,o);
  console.log("skill",num,"delay",before,"->",ms);
}
out.writeUInt32LE(checksum(out,DATA,KEY),DATA);
fs.writeFileSync("skill_eng_ag.bmd",out);
// verify round trip
const v=Buffer.from(fs.readFileSync("skill_eng_ag.bmd"));
console.log("new checksum ok:", v.readUInt32LE(DATA)===checksum(v,DATA,KEY));
for(const i of [344,346,41]){ const r=Buffer.from(v.subarray(i*S,(i+1)*S)); for(let j=0;j<S;j++) r[j]^=key3[j%3]; console.log(i, r.toString("utf8",0,50).replace(/\0.*$/,""), "delay="+r.readInt32LE(64)); }
