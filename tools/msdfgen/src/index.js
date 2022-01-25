(async function(){

//https://soimy.github.io/msdf-bmfont-xml/
//https://www.charset.org/charsets/iso-8859-3

if(!process.argv[2]){
    console.error(`No font provided!`);
    await new Promise(resolve => setTimeout(resolve, 2000));
    return;
} 
console.log(`Font: ${process.argv[2]}`);


const generateBMFont = require('msdf-bmfont-xml');
const fs = require('fs');

const opt = {
    binary:"msdfgen.exe",
    outputType: 'json',
    border : 3,
    fontSize: 32,
    charset:' !"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~¡¢£¤¥¦§¨©ª«¬®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œžŸ'
};

const font = process.argv[2];//'Lato-Regular.ttf'

generateBMFont(font, opt, (error, textures, font) => {
  if (error) throw error;
  textures.forEach((texture, index) => {
    fs.writeFile(texture.filename+".png", texture.texture, (err) => {
      if (err) throw err;
    });
  });
  fs.writeFile(font.filename, font.data, (err) => {
    if (err) throw err;
  });
});

})();