var nParioObj={newClient:function (ck){var doseg=0;var pixsvc="svc.npario-inc.net/DMP/";var lp="http"+(location["protocol"]=="https:"?"s":"")+"://";var pixurl=lp+"svc.npario-inc.net/DMP/";if( typeof (pixsvc)!=="undefined"){pixurl=lp+pixsvc;} ;var payload="";var jl="";var url="\x26loc="+encodeURIComponent(encodeURIComponent(window["location"]["href"]));var ref="\x26ref="+encodeURIComponent(encodeURIComponent(document["referrer"]));var b=Math["floor"](1000000*Math["random"]());pixurl=pixurl+b+".jx?";if( typeof (ll)!=="undefined"){payload=payload+"l="+ll+url+ref;} else {payload=payload+"l=1"+url+ref;} ;return {setPixSvc:function (svc){pixsvc=svc;} ,addKV:function (k,v){payload=payload+"\x26"+k+"="+v;} ,addKVMulti:function addKVMulti(k,v){for(var i=0;i<v["length"];i++){this["addKV"](k,v[i]);} ;} ,setPayload:function (_jl){_jl=_jl["replace"](/\+/g,"%20");jl=_jl;} ,addKVAndPixel:function (k,v){payload=payload+"\x26"+k+"="+v;this["pixel"]();} ,addKVMultiAndPixel:function addKVMulti(k,v){for(var i=0;i<v["length"];i++){this["addKV"](k,v[i]);} ;this["pixel"]();} ,pixel:function (){var gpixurl=lp+pixsvc+b+".jx?"+payload+"\x26"+jl;var jsscript=document["createElement"]("script");jsscript["setAttribute"]("type","text/javascript");jsscript["src"]=gpixurl+"\x26seg="+doseg;var s=document["getElementsByTagName"]("script")[0];if(doseg==1){s=document["getElementsByTagName"]("script")[0];s["parentNode"]["insertBefore"](jsscript,s);} else {var p=document["body"]==null?document["getElementsByTagName"]("head")[0]:document["body"];p["appendChild"](jsscript);} ;} ,setSegmentation:function (){doseg=1;} ,setUID:function (guid){trid=guid;} ,setSegs:function (segs){npsegs=segs;} };} };
var np_C767=nParioObj.newClient("C767");
np_C767.setPayload("ck=C767&e=76706&src=tag");
np_C767.setPixSvc("pix.npario-inc.net/DMP/");
np_C767.pixel();
var nParioUtils={newClient:function (ck){var p=document["body"]==null?document["getElementsByTagName"]("head")[0]:document["body"];return {mi:function (u,h,w){var e=document["createElement"]("iframe");e["height"]=h?h:0;e["width"]=w?w:0;e["frameBorder"]=0;e["src"]=u;} ,mj:function (u){var e=document["createElement"]("script");e["language"]="JavaScript";e["type"]="text/javascript";e["src"]=u;p["appendChild"](e,p["firstChild"]);} ,mg:function (u){var i= new Image(1,1);i["src"]=u;p["appendChild"](i,p["firstChild"]);} ,gs:function (){return "http"+(location["protocol"]=="https:"?"s":"");} };} };
var nu_C767=nParioUtils.newClient("C767");
nu_C767.mg('//api.bizographics.com/v2/profile.redirect?api_key=d3937bab6d994096a97ca38f0c3703be&callback_url=https%3A%2F%2Fsvc.npario-inc.net%2FDMP%2FC767%2Fbizo.gif');
nu_C767.mg('//loadr.exelator.com/load/?p=104&g=540&ck=C767&j=0');
