if(typeof window.staticTime=="undefined")
	window.staticTime=new Date().getTime();

if( typeof console==="undefined" ){
	console = {
		log: function(){},
		dir: function(){}
	};
}
/*
try{
    //防止页面被iframe嵌入
    if (!scope.$allowIframe && top.location !== self.location && "searchToQing" !== scope.$pageid) {
        top.location = self.location;
    }
}catch(e){
    
}
*/

if( typeof $_GLOBAL==="undefined" ){
	$_GLOBAL = {};
}
$_GLOBAL.DOMAIN_CORE = "http://qing.weibo.com/";

// pageid.js version
$_GLOBAL.ver = {
	xblog : "122"
};

(function (){
    //boot加载JS时间统计标记
    if(typeof ___begin_time == "undefined")
        ___begin_time = +new Date(); 
	//- debug -
	var __debug_mode = false, //should be false
    
	//- sina lib version - TODO 
        __sina_ver = "0.0.1",
	
	// js base domain
        __js_domain = "http://sjs.sinajs.cn/";
	
	// @desc add DOM onload Event
	var __addDOMLoadEvent = function(func){
	    var __load_events;
	    var __load_timer;
//		var binded = false;
	    if (!__load_events) {
	        var init = function(){
	            // quit if this function has already been called
	            if (arguments.callee.done) {
	                return;
	            }
	            // flag this function so we don't do the same thing twice
	            arguments.callee.done = true;
	            // kill the timer
	            if (__load_timer) {
	                clearInterval(__load_timer);
	                __load_timer = null;
	            }
                
	            // execute each function in the stack in the order they were added
	            for (var i = 0; i < __load_events.length; i++) {
                    var func = __load_events[i];
                    if(!func.done){
                        func.done = true;
                        func();
                    }
	            }
                var loadTime = +new Date() - ___begin_time, win = window;
                if(typeof xblogLog == "function" && win.Lib && win.Lib.checkAuthor){
                    Lib.checkAuthor();
                    window.$UID && xblogLog("A_9999_99_99|time="+loadTime, window.$UID);
                }
                //console.log("页面onload:"+runTime);
	            __load_events = null;
				//图片懒加载变成常态
				if(!scope.$noAutoImg) {
					var imgs = document.getElementsByTagName("img");
					for(var i=0,n=imgs.length;i<n;i++){
						var s = imgs[i].getAttribute("real_src");
						if(s) imgs[i].setAttribute("src",s);
					}
				}
	        };
	        // for Mozilla/Opera9
	        if (document.addEventListener) {
	            document.addEventListener("DOMContentLoaded", init, false);
//				binded = true;
	        }
	        // for Internet Explorer
	        /*@cc_on @*/
	        /*@if (@_win32)
	         var domlen = document.getElementsByTagName("*").length;
	         var domnum = 0;
	         (function () {
	         if(domnum != domlen) {
	         setTimeout(arguments.callee, 500);
	         }
	         else {
	         setTimeout(init, 500);
	         }
	         domnum = domlen;
	         })();
	         @end @*/
	        // for Safari
	        if (/WebKit/i.test(navigator.userAgent)) { // sniff
	            __load_timer = setInterval(function(){
	                if (/loaded|complete/.test(document.readyState)) {
	                    init(); // call the onload handler
//	                    binded = true;
	                }
	            }, 10);
	        }
	        // for other browsers
//			if(binded == false){
				window.onload = init;
//			}
	        // create event function stack
	        __load_events = [];
	    }
	    // add function to event stack
	    __load_events.push(func);
	};
	
	// 绑定事件
	var addEvent = function(elm, func, evType, useCapture) {
		var _el = $E(elm);
		if(_el == null){ return; }
		if(typeof useCapture == "undefined"){
			useCapture = false;
		}
		if(typeof evType == "undefined"){
			evType = "click";
		}
		if(_el.addEventListener){
			_el.addEventListener(evType, func, useCapture);
			return true;
		}else if(_el.attachEvent){
			var r = _el.attachEvent("on" + evType, func);
			return true;
		}else{
			_el['on' + evType] = func;
		}
	};
	var __addFocusEvent = function(fFocusFunction){
		//TODO not available during the dev
		if(window.excute != null && typeof window.excute == "function"){
			excute();
			excute = null;
		}
	};
	if(__debug_mode){
		document.write('<script type="text/javascript" src="' + __js_domain + 'bind2/debug/debug_base.js"></script>');
		document.write('<script type="text/javascript" src="' + __js_domain + 'bind2/debug/debug.js"></script>');
	}
	
	window.__load_js = function(){
	    var url = "";
		if(__debug_mode == true){
			url = 	__js_domain + "bind2/index.php?product=" + scope.$PRODUCT_NAME + "&pageid=" + scope.$pageid
						+ "&rnd=" + new Date().getTime();
		}else{
			// 取得 JS 版本号
			var jsver =	(typeof $_GLOBAL != "undefined" && $_GLOBAL.ver != null)
							? $_GLOBAL.ver[scope.$PRODUCT_NAME] || "-1"
							: "-1";
			url = 	__js_domain + scope.$PRODUCT_NAME + "/" + scope.$pageid + ".js?"
					+ jsver + ".js";
		}
		function render_page(){
			__addDOMLoadEvent(main);
			addEvent(document.body, __addFocusEvent, "focus");
			addEvent(window, __addFocusEvent, "scroll");
			addEvent(document.body, __addFocusEvent, "mousemove");
			addEvent(document.body, __addFocusEvent, "mouseover");
		}
		function report_error(time){
			clearTimeout(loadCheck);loadCheck = null;
			report_error = function (){};
		}
		if(__debug_mode == true){
			window.__render_page = render_page;
			document.write('<script src="' + url +'" charset="utf-8"></script>');
		} else {
			var js = document.createElement("script");
			js.src = url;
			js.charset = "utf-8";
			js.onload = js.onreadystatechange = function () {
				if (js && js.readyState && js.readyState != "loaded" && js.readyState != "complete") {
					return;
				}
				js.onload = js.onreadystatechange = js.onerror = null;
				js.src = "";
				js.parentNode.removeChild(js);
				js = null;
				clearTimeout(loadCheck);loadCheck = null;
				if(typeof main != "undefined"){ render_page(); } else { report_error(); }
			};
			js.onerror = function () {
				js.onload = js.onreadystatechange = js.onerror = null;
				js.src = "";
				js.parentNode.removeChild(js);
				js = null;
				clearTimeout(loadCheck); loadCheck = null;
				report_error();
			};			
			var startTime = new Date().getTime();
			document.getElementsByTagName("head")[0].appendChild(js);
			var loadCheck = setTimeout(function () {
				report_error(-1);
			}, 30000);
		}
	};
	window.__render_page = function(){};
	
	if (typeof scope.$setDomain == "undefined" || scope.$setDomain == true) {
		document.domain = "weibo.com";
	}
	if(/\(iP(hone|ad|od)/i.test(navigator.userAgent) == false){return;}
	document.addEventListener('mouseover', function(e){
		var ele = e.target;
		do{
			if(ele.tagName == 'A'){
				ele.target = '_self';
				return;
			}
			if(ele.tagName == 'DIV'){return;}
			ele = ele.parentNode;
		}while(ele);
	},false);
})();
