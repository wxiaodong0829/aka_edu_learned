var SpaceAPI4Passport=SpaceAPI4Passport||{};(function(e){e.version="2";e.loaded=true;e.ext=e.ext||{};var d=window.location.host;var a={passport:"http://passport.baidu.com/",pop:{relay:"http://"+d+"/st/jump_v2_passport.html",reg:"http://hi.baidu.com/reg/new"},login:{staticpage:"http://"+d+"/st/jump_v2_login.html",action:"http://passport.baidu.com/v2/?login",resendmail:"http://hi.baidu.com/reg/verify/mail?type=resendMail&email=#{mail}"}};var b=(function(){var h=function(r,t,p,s){var q={type:s,no:t};q.title=t>-1?"��¼ʧ��":"��ʾ��Ϣ";t=t+"";switch(t){case"-21":q.description="������ʹ���û�����¼�����û���̫������������7�����ֻ�14���ֽڣ�";break;case"-11":q.description="������ʹ�������¼��������̫������������60���ֽڣ�";break;case"-3":q.description="�ֻ��Ÿ�ʽ�������������롣��С�ڻ����11λ�����֣�";break;case"-2":switch(s){case"username":q.description="����д�˺�";break;case"phonenumber":q.description="����д�ֻ���";break;case"password":q.description="����д����";break;case"verifycode":q.description="��������֤��";break;default:q.title=""}break;case"-1":q.description="��¼ʱ����δ֪��������������";break;case"1":switch(s){case"phonenumber":q.description="�ֻ��Ÿ�ʽ��������������";break;case"username":default:q.description="�û�����ʽ��������������"}break;case"2":switch(s){case"username":q.description="�û�������";break;case"phonenumber":q.description="�ֻ��Ų�����";break;default:q.description="�˺Ų�����"}break;case"4":q.description="��¼������������µ�¼";break;case"5":q.description="���յ�¼��������";break;case"6":q.description="��֤�벻ƥ�䣬������������֤��";break;case"16":q.description="�Բ����������޷���¼";break;case"20":q.description="���ʺ��ѵ�¼��������";break;case"257":q.description="��������֤��";break;case"110024":q.title="�˺�δ����";var o=a.login.resendmail;var n=p.mail;o=baidu.string.format(o,{mail:n});q.description=["�뵽��֤�ʼ��м��<br />����",'<a href="',o,'" class="blueA">�ط���֤�ʼ�</a>'].join("");break;default:}g(r,q)};var j=[];var l=function(o){if(!o||!o.id){return}var p=o.id+"Tip";var n=baidu.g(p);if(!n||n==p){return}baidu.dom.remove(n)};var m="tip";var g=function(r,q){if(m=="alert"){alert(q.description);return}if(j[r.id]){clearTimeout(j[r.id]);j[r.id]=0}var t=r.id+"Tip";var p=baidu.g(t);if(p&&p!=t){baidu.dom.remove(p)}var q=q||{};if(!q.title){return}var s=baidu.dom.getParent(r);baidu.dom.addClass(s,"tip_form_login_container");p=baidu.dom.create("div",{id:t,className:"tip_form_login"});var o=parseInt(s.offsetHeight,10)+6;baidu.dom.setStyle(p,"bottom",o);p.innerHTML=['<div class="tip_form_login_body">','<div class="tip_form_login_title">',q.title,"</div>",'<div class="tip_form_login_description">',q.description,"</div>",'<div class="tip_form_login_close">&#160;</div>','<div class="tip_form_login_down_arrow">&#160;</div>',"</div>"].join("");baidu.dom.insertAfter(p,r);var n=baidu.q("tip_form_login_close",p)[0];baidu.on(n,"click",function(u){l(r)});j[r.id]=setTimeout(function(){baidu.event.fire(n,"click")},3000)};var k=function(n,o,p){window.location.href=n};var i=function(u){var s=u.outDomId;var o=u.staticpage||SpaceAPI4Passport.ext.staticpage||a.login.staticpage;var r=u.isPhone?true:false;var p=u.isMen===false?false:true;var t=u.isTopBar?true:false;m=u.errorType||m||"tip";var n=a.login.action;var q={outerDomId:s,staticpage:u.staticpage||o,u:u.u||window.location.href,isPhone:r,isMen:p,onReady:u.onReady||function(x){baidu.dom.addClass(x,"form_login_container");if(!t){baidu.dom.addClass(x,"form_login_container_normal");var y=baidu.q("pass_login_label_password",x)[0];var v=baidu.q("pass_login_label_verifycode",x)[0];y.innerHTML="�ܡ��룺";v.innerHTML="��֤�룺";var w=baidu.q("pass_login_label_username",x)[0];w.innerHTML="�ˡ��ţ�"}else{baidu.dom.addClass(x,"form_login_container_topbar")}if(r){return}var B=baidu.q("pass_login_input_username",x)[0];var A="�û���/��֤����";if(t){A="�û���/����"}if("placeholder" in B){baidu.dom.setAttr(B,"placeholder",A)}else{var z=function(D,F,C){var E=D.value;if(E===""&&C){setTimeout(function(){D.value=F},1);baidu.dom.addClass(D,"input_is_placeholder")}if(E===F&&!C){D.value="";baidu.dom.removeClass(D,"input_is_placeholder")}};z(B,A,true);baidu.on(B,"keyup",function(C){z(B,A)});baidu.on(B,"focus",function(C){z(B,A)});baidu.on(B,"blur",function(C){z(B,A,true)})}if(u.afterReady){u.afterReady(x)}},onInputErr:u.onInputErr||function(w,z,v){var y=baidu.dom.getAncestorByClass(w,"form_login_container");if(t){if(z>-1){k(n,y,u)}return}var x;if(r){x=baidu.dom.hasClass(w,"pass_login_input_phoneNumber")?"phonenumber":x}else{x=baidu.dom.hasClass(w,"pass_login_input_username")?"username":x}x=baidu.dom.hasClass(w,"pass_login_input_password")?"password":x;x=baidu.dom.hasClass(w,"pass_login_input_verifycode")?"verifycode":x;h(y,z,v,x)},onInputOk:u.onInputOk||function(w){if(t){return}var v=baidu.dom.getAncestorByClass(w,"form_login_container");l(v)},onCheckErr:function(v){if(t){k(n,v,u);return}},onSystemErr:u.onSystemErr||function(x,w,v){if(t){if(w>-1){k(n,x,u)}return}h(x,w,v,"general")}};bdPass.api.login.init(q)};return i})();var c={};c.show=function(h){var i=h||{};var g=i.type||"login";if(g=="login"){pass_pop_api({action:"emailLogin",relay:i.relay||SpaceAPI4Passport.ext.relay||a.pop.relay,useSkinFromPass:false,skin:"http://hi.bdimg.com/static/base/css/passportV2/pop_skin.css?v=b56252d7.css",callback:function(j){var k=i.reloadUrl||false;if(k=="noreload"){return}k?window.location.href=k:location.reload()},tpl:"sp"})}else{window.location.href=a.pop.reg}};c.callback=function(h){var g=h||{};if(g.type&&g.type=="reg"){window.location.href=a.pop.reg}else{pass_pop_run(h)}};var f=function(h){h=h||{};a=h.url||a;var g="true";document.write('<script type="text/javascript" src="'+a.passport+"v2/api/?getapi&class=login&tpl=sp&tangram="+g+'"><\/script>');document.write('<script id="pass_api_login_shell" charset="utf-8"><\/script>');document.write('<script src="'+a.passport+'js/pass_api_pop_shell.js" charset="utf-8"><\/script>')};e.init=f;e.pop=c;e.login=b})(SpaceAPI4Passport);SpaceAPI4Passport.init();