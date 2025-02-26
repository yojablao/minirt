<!--

function findBaloon(target){
	var link=target.childNodes[0];
	var baloon=target.nextSibling;
	return baloon;
}

function hasClass(ele,cls) {
	return ele.className.match(new RegExp('(\\s|^)'+cls+'(\\s|$)'));
}

function addClass(ele,cls) {
	if (!this.hasClass(ele,cls)) ele.className += " "+cls;
}

function removeClass(ele,cls) {
	if (hasClass(ele,cls)) {
    	var reg = new RegExp('(\\s|^)'+cls+'(\\s|$)');
		ele.className=ele.className.replace(reg,' ');
	}
}

function getElementsByClass(searchClass,node,tag) {
	var classElements = new Array();
	if ( node == null )
		node = document;
	if ( tag == null )
		tag = '*';
	var els = node.getElementsByTagName(tag);
	var elsLen = els.length;
	var pattern = new RegExp("(^|\\s)"+searchClass+"(\\s|$)");
	for (i = 0, j = 0; i < elsLen; i++) {
		if ( pattern.test(els[i].className) ) {
			classElements[j] = els[i];
			j++;
		}
	}
	return classElements;
}

function closeOtherBalloons(baloon)
{
	var myclass = new RegExp('\\bmouse\\b');
	
	var els = document.getElementsByTagName('div');
	var elsLen = els.length;
	for (i = 0; i < elsLen; i++) {
		if ( myclass.test(els[i].className) ) {
			if (els[i] != baloon)
			{
				removeClass(els[i], 'mouse');
				els[i].style.display = 'none';
			}
		}
	}
}

function ShowPopup(sender)
{
	var baloon=findBaloon(sender);
	baloon.style.display = 'block';
	addClass(sender, 'mouse');
	/*
	if (!baloon.onmouseover)
	{*/
		baloon.onmouseover=function(){
			addClass(baloon, 'mouse');
		};/*
	}
	*/
	/*
	if (!baloon.onmouseout)
	{*/
		baloon.onmouseout=function(){
			removeClass(baloon, 'mouse');
			setTimeout(function() {
				closePopup(sender);
				//baloon.style.display = 'none';
			}, 300);
		};
	/*}*/
	closeOtherBalloons(baloon);
}

function HidePopup(sender)
{
	removeClass(sender, 'mouse');
	setTimeout(function() {closePopup(sender);}, 700);
}

function closePopup(sender){
	var baloon=findBaloon(sender);
	if (!hasClass(baloon, 'mouse') && !hasClass(sender, 'mouse')){
		baloon.style.display = 'none';
	}
}

-->
