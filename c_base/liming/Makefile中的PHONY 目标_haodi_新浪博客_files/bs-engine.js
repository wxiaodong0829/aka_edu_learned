(function(i,g){var d=i.bShareUtil,k=i.bShareControl,l=g.body,m=g.documentElement;d.createShareBox=function(j,b){var e=i[j];if(e.isLite){var f=g.createElement("div");f.innerHTML='<div id="bsBox" style="display:none;"></div>';l.appendChild(f)}else e.isOpen=!1,e.bsBox=null,e.create=function(){d.loadStyle("#bsBox{z-index:100000001;background:transparent;padding:0;margin:0;border:none;width:"+b.boxWidth+"px;height:"+b.boxHeight+"px;}#bsClose{_overflow:hidden;cursor:pointer;position:absolute;color:#666;font-weight:bold;font-family:Arial,\u5b8b\u4f53,sans-serif;font-size:12px;line-height:normal;}");
var a=g.createElement("div"),c='<div id="bsBox" style="display:none;"><div id="bsClose">X</div><iframe id="bShareFrame" name="bsFrame'+Math.floor(Math.random()*1E3)+'" frameborder="0" scrolling="no" allowtransparency="true" transparency="true"></iframe></div>';a.innerHTML=c;l.appendChild(a);e.bsBox=g.getElementById("bsBox");g.getElementById("bsClose").onclick=function(){e.disappear()}},e.resetBox=function(a,c){b[a]=c},e.show=function(a){e.isOpen?e.disappear():(e.prepare(a),e.load(),e.display())},
e.display=function(){b.position=b.position||0;switch(b.position){case 0:var a=(d.getWH().w-b.boxWidth)/2,c=(d.getWH().h-b.boxHeight)*2/5,h=Math.max(m.scrollTop,l.scrollTop);e.bsBox.style.position=d.isQk()?"absolute":"fixed";e.bsBox.style.left=(a>0?a:0)+"px";e.bsBox.style.top=(d.isQk()?h:0)+(c>20?c:20)+"px";break;case 1:h=d.getElem(g,"a",b.anchor)[e.curb],a=d.getOffset(h).y,c=d.getOffset(h).x,h=h.offsetHeight,e.bsBox.style.position="absolute",e.bsBox.style.left=c+"px",e.bsBox.style.top=a+h+2+"px"}a=
g.getElementById("bsClose");a.style.top=b.closeTop+"px";a.style.right=b.closeRight+"px";a=g.getElementById("bShareFrame");a.style.height=b.boxHeight+"px";a.style.width=b.boxWidth+"px";e.bsBox.style.height=b.boxHeight+"px";e.bsBox.style.width=b.boxWidth+"px";e.bsBox.style.display=""},e.disappear=function(){e.bsBox.style.display="none";e.isOpen=!1},e.initBox=function(){e.create();l.onclick=function(){e.isOpen&&e.disappear()}}};d.loadEngine=function(j){var b=i[j],e=b.config,f=b.params;b.prepare=function(a){var c=
{};typeof a==="object"?c=a:(b.curb=a===void 0?b.curb:a,b.curb>=0&&(c=b.entries[b.curb]||{}));f.url=c.url||f.url||i.location.href;f.title=c.title||f.title||g.title;f.summary=c.summary?d.shortenText(c.summary,110):f.summary||d.getContent();f.lang=f.request_locale=e.lang;f.pics=c.pics||d.getPics();f.pic=c.pic||f.pic;for(var h in c)/(url|title|summary|content)/.test(h)||(f[h]=c[h])};b.share=function(a,c,h){b.prepare(h);b.load(c)&&b.afterLoad&&b.afterLoad();d.stopProp(a)};b.stats=function(a,c,h){b.prepare(h);
b.shareStats(c);d.stopProp(a)};b.shareStats=function(a){var c=b.bhost+"/bshare_share_statistics?";c+="site="+a;c+="&url="+d.encode(f.url);c+="&title="+d.encode(f.title);c+="&publisherUuid="+f.publisherUuid;c+="&type="+f.type;d.loadScript(c)};b.view=function(a){if(!k.viewed){k.viewed=!0;var c=b.bhost+"/bshare_view?Callback="+j+".viewcb&";c+="url="+d.encode(a);c+="&h="+d.encode(i.location.hash);c+="&uuid="+f.publisherUuid;e.showShareCount&&(c+="&sc=1");c+=b.bpsCount?"&l="+b.bpsCount:"&l=17";this.isLite&&
(c+="&lite=1");if(g.referrer)a=g.createElement("a"),a.href=g.referrer,c+="&ref="+d.encode(a.host);d.loadScript(c)}};b.click=function(){if(!k.clicked&&(k.clicked=!0,b.preb!==b.curb)){b.preb=b.curb;var a=b.bhost+"/bshare_click?";a+="url="+d.encode(b.params.url);a+="&title="+d.encode(b.params.title);a+="&uuid="+f.publisherUuid;d.loadScript(a)}};b.promote=function(){f.promote=!0;b.resetBox("boxHeight",588);if(e.style===3){if(e.text===b.iL8n.shareText)e.text=b.iL8n.shareTextPromote}else if(e.style!==4&&
e.style!==5){var a=function(a){a.style.position="relative";a.style.overflow="visible";var h=d.isQk()||(g.documentMode?parseInt(g.documentMode,10)===7:d.isIe7);a.style.display=h?"inline":"inline-block";if(h)a.style.zoom="1";d.getElem(a,"div","bsPromo",function(a){a.style.display="block";a.innerHTML=b.iL8n.promote})};d.getElem(g,"a","bshareDiv",function(c){a(c,d.getElem(c,"div","bsPromo")[0])});d.getElem(g,"div","bshare-custom",function(c){var b=g.createElement("div");b.className="bsPromo";c.insertBefore(b,
c.childNodes[0]);a(c,b)})}};b.viewcb=function(a,c,d,g,f){k.bShareLoad=!0;a&&b.entries.length===0&&b.showCount(a);if(c)b.user=c;if(d&&d.length>0)e.bps=d;f&&!b.isLite&&typeof b.promote==="function"&&b.promote();(c||d)&&typeof b.ready==="function"&&b.ready()};b.count=function(a){if(e.showShareCount){var c=b.bhost+"/bshare_share_count?Callback="+j+".showCount";c+="&url="+d.encode(a);d.loadScript(c)}};b.shareCount=function(a,c){/0|2|10/.test(e.style)?a=d.longRound(a):/11/.test(e.style)||(a=d.shortRound(a));
var b={cssFloat:"none"};if(j!=="bShareLike")switch(e.style){case 1:b.left="36px";b.color="#fff";b.fontsize="12px";break;case 10:b.left="27px";case 0:case 2:b.fontsize="11px";break;case 11:b.top="25px",b.fontsize="17px"}if(c){var f=c.style,g;for(g in b)if(g!=="color"||!f.color)f[g]=b[g];c.innerHTML=d.addCommas(a)}else return d.addCommas(a)};b.showCount=function(a){b.counters=a;var c=d.getElem(g,"span","shareCount");if(!c||c.length===0)c=d.getElem(g,"span","BSHARE_COUNT");var h,e;if(typeof a==="number"){for(h=
0,e=c.length;h<e;h++)b.shareCount(a,c[h]);d.getElem(g,"span","BSHARE_COUNT",function(c){c.innerHTML=""+b.shareCount(a,null)})}else if(a.length>0){e=a.length;for(h=0;h<e;h++)b.shareCount(a[h],c[h]);for(h=e-1;h<c.length;h++)b.shareCount(a[e-1],c[h])}};b.updateCounter=function(){typeof b.counters==="number"?b.counters+=1:b.counters[b.curb]+=1;b.showCount(b.counters)};d.roundNumber=function(a,c){try{return Math.round(a*Math.pow(10,c))/Math.pow(10,c)}catch(b){return a}};d.longRound=function(a){if(a>999999)return d.roundNumber(a/
1E6,2)+"M";else if(a>99999)return d.roundNumber(a/1E3,1)+"K";return a};d.shortRound=function(a){if(a>999999)return d.roundNumber(a/1E6,1)+"M";else if(a>99999)return d.roundNumber(a/1E3,0)+"K";else if(a>9999)return d.roundNumber(a/1E3,1)+"K";else if(a>999)return d.roundNumber(a/1E3,2)+"K";return a};d.addCommas=function(a){try{a+="";for(var c=a.split("."),b=c[0],d=c.length>1?"."+c[1]:"",c=/(\d+)(\d{3})/;c.test(b);)b=b.replace(c,"$1,$2");return b+d}catch(e){return a}};d.shortenText=function(a,b){a=a||
"";return a.length>b?a.substring(0,b)+"...":a};d.getCurrentSelection=function(){var a="";if(i.getSelection)a=i.getSelection().toString();else if(g.getSelection)a=g.getSelection;else if(g.selection)try{a=g.selection.createRange().text}catch(b){}return a};d.grabTextContent=function(){for(var a="",b=g.getElementsByTagName("p"),e=0,f=b.length;e<f;e++){var i=b[e];if(i.id==="BSHARE_TEXT"||i.className.indexOf("BSHARE_TEXT")!==-1)a+=d.getText(i)}a===""&&d.getElem(g,"meta",null,function(b){var c=b.getAttribute("name");
c&&c.toLowerCase()==="description"&&(a=b.getAttribute("content"))});return a};d.getContent=function(){var a=null,b=d.getCurrentSelection();return b?d.shortenText(b,110):(a===null&&(a=d.grabTextContent()),d.shortenText(a,110))};d.getPics=function(){for(var a="",b=d.getElem(g,"img"),e=0,f=b.length;e<f;e++){var i=b[e];if(!(i.offsetHeight<=119||i.offsetWidth<=119)){if(a.length+i.src.length>=1500)break;a!==""&&(a+="|");a+=i.src}}return a};d.removeUrlHash=function(a){var b=a.indexOf("#");b>0&&(a=a.substr(0,
b));return a};d.showClipboardSuccess=function(){alert(b.iL8n.copySuccess)};d.showClipboardUnsupportBrowsertxt=function(a){prompt(b.iL8n.copyTip,a)};d.copy2Clipboard=function(){try{var a=d.removeUrlHash(f.url),b=f.title+" "+a,e=i.clipboardData;e?(e.clearData(),e.setData("Text",b),d.showClipboardSuccess()):d.showClipboardUnsupportBrowsertxt(b)}catch(g){}};d.add2Printer=function(){i.print()};d.add2Bookmark=function(){if(i.sidebar)i.sidebar.addPanel(f.title,f.url,"");else if(i.chrome)alert(b.iL8n.bookmarkTip);
else if(i.external)try{i.external.AddFavorite(f.url,f.title)}catch(a){}else if(i.opera&&i.print)return!0;else alert(b.iL8n.notSupport)}}})(window,document);
