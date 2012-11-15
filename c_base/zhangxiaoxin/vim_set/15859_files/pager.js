function iwmsPager(curPage, sumPage, rewrite){
	this.cur=curPage;
	this.sum=sumPage;
	this.rewrite=rewrite;
}

iwmsPager.prototype.GetUrl=function(p){
	if (p<=0){p=1;}
	if (p>this.sum){p=this.sum;}
	var u = location.href;
	if (!this.rewrite){
		if (u.indexOf("?")<0){
			u="?";
		}else{
			u=u.substr(u.indexOf("?"));
		}
		u=u.replace(/page=\d+&?/ig,"");
		if (p>1){
			if(u!="?"){
				u=u.replace("?","?page="+p+"&");
			}else{
				u=u.replace("?","?page="+p);
			}
		}
	}else{
		u=u.substr(u.lastIndexOf("/")+1);
		u=u.replace(/p\d+/ig,"");
		if (p>1){
			u=u.replace(".","p"+p+".");
		}
	}
	return u;
}

iwmsPager.prototype.Jump=function(){
	var n = document.getElementById("goPage").value;
	n = parseInt(n);
	if (isNaN(n)){return;}
	location=this.GetUrl(n);
}

iwmsPager.prototype.Next=function(){
	if (this.sum==1)return;
	var n=this.cur==this.sum?1:this.cur+1;
	location=this.GetUrl(n);
}

iwmsPager.prototype.Prev=function(){
	if (this.sum==1)return;
	var n=this.cur==1?this.sum:this.cur-1;
	location=this.GetUrl(n);
}

function keyPage(event){
	if (typeof(pager)!="undefined"){
		event = event ? event : (window.event ? window.event : null); 
		if (event.keyCode==37) pager.Prev();
		if (event.keyCode==39) pager.Next();
	}
}

document.onkeydown=keyPage;
