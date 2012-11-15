
var cloudad_urls = [
'http://ad.csdn.net/adsrc/cloud-bbs-homepage_760-90-0726.swf'
];
var cloudad_clks = [
'http://e.cn.miaozhen.com/r.gif?k=1002376&p=3xw7q0&o=http://ad-apac.doubleclick.net/click;h=v2|3F81|0|0|%2a|y;259610168;0-0;0;83764567;31-1|1;49192013|49187316|1;;%3fhttp://www.ibm.com/systems/cn/ads/2012q1_bcfc.shtml?csr=apch_cfg3_20120711_1342010369796&ck=csdn&cmp=215ff&ct=215ff06w&cr=csdn&cm=b&csot=-&ccy=cn&cpb=-&cd=2012-07-10&cot=a&cpg=off&cn=intel_cloud_-blade_foundation_for_cloud&csz=760*90'
];

var can_swf = (function(){
	if(document.all) swf = new ActiveXObject('ShockwaveFlash.ShockwaveFlash');
	else if(navigator.plugins) swf = navigator.plugins["Shockwave Flash"];
	return !!swf;
})();

function cloudad_show() {
    var rd = Math.random();
    var ad_url, log_url;
    if (rd < 0.8 && can_swf) {
        ad_url = cloudad_urls[0];

        log_url = 'http://ad.csdn.net/log.ashx';
        log_url += '?t=view&adtype=ibm6&adurl=' + encodeURIComponent(ad_url);
        cloudad_doRequest(log_url, true);
    }
    if (rd < 0.002) {
        ad_url = cloudad_clks[0];

        log_url = 'http://ad.csdn.net/log.ashx';
        log_url += '?t=click&adtype=ibm6&adurl=' + encodeURIComponent(ad_url);
        cloudad_doRequest(log_url, true);
    }
}

function cloudad_doRequest(url, useFrm) {
    var e = document.createElement(useFrm ? "iframe" : "img");

    e.style.width = "1px";
    e.style.height = "1px";
    e.style.position = "absolute";
    e.style.visibility = "hidden";

    if (url.indexOf('?') > 0) url += '&r_m=';
    else url += '?r_m=';
    url += new Date().getMilliseconds();
    e.src = url;

    document.body.appendChild(e);
}

setTimeout(function () {
    cloudad_show();
}, 1000);
