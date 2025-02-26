<!--
var XmlHttpRequestObject;
var LastID;
var LastIDName;
function GetAjaxReadyState()
{
	return XmlHttpRequestObject.readyState;
}

function GetAjaxResponseText()
{
	return XmlHttpRequestObject.responseText;
}

function GetAjaxStatus()
{
	return XmlHttpRequestObject.status;
}


function initRequestObject()
{
	XmlHttpRequestObject = null;
	var msxmlhttp = new Array(
		'Msxml2.XMLHTTP.7.0',
		'Msxml2.XMLHTTP.6.0',
		'Msxml2.XMLHTTP.5.0',
		'Msxml2.XMLHTTP.4.0',
		'Msxml2.XMLHTTP.3.0',
		'Msxml2.XMLHTTP',
		'Microsoft.XMLHTTP');
	for (var i = 0; i < msxmlhttp.length; i++) 
	{
		try 
		{
			XmlHttpRequestObject = new ActiveXObject(msxmlhttp[i]);
			if (XmlHttpRequestObject!=null) break;
		} 
		catch (e) 
		{
			XmlHttpRequestObject = null;
		}
	}
	if(!XmlHttpRequestObject && typeof XMLHttpRequest != "undefined")
			XmlHttpRequestObject = new XMLHttpRequest();
}

function BeginAjaxRequest(url, processReqChange)
{
	initRequestObject();
	if (XmlHttpRequestObject!=null) 
	{
		XmlHttpRequestObject.onreadystatechange = processReqChange;
		XmlHttpRequestObject.open("GET", url, true);
		XmlHttpRequestObject.setRequestHeader('If-Modified-Since', 'Wed, 15 Nov 1995 00:00:00 GMT');		
		XmlHttpRequestObject.send("");
	}
}

Function.emptyFunction = Function.emptyMethod = function() 
{
}

function AbortAjaxRequest()
{
	if (XmlHttpRequestObject)
	{
		XmlHttpRequestObject.onreadystatechange = Function.emptyMethod;
		XmlHttpRequestObject.abort();
		XmlHttpRequestObject = null;
	}
}

/*function ReconnectFrontpageItems()
{
	AbortAjaxRequest();
	LastIDName = 'frontpageitems';
	BeginAjaxRequest("/filters/frontpageitems.php", processReqChange);
}

function ReconnectClosePopup()
{
	AbortAjaxRequest();
	LastIDName = 'yellowpopup';
	BeginAjaxRequest("/filters/closefrontpageitems.php", processReqChange);
}

function Reconnect(id)
{
	LastIDName = 'content';
	id=prepareTabIndex(id);
	AbortAjaxRequest();
	LastID = id;
	BeginAjaxRequest("/filters/get_tab_data.html?id="+id, processReqChange);
}
*/
function generateErrorString(str)
{
	return "<p class=\"error-tabs\"><span class=\"red\"><b>Error.</b></span>&nbsp;Server reports: " + str + "</p>";
}

function processReqChange()
{
	if (GetAjaxReadyState() == 4) 
	{                 	
		ShowContent();
		result = GetAjaxResponseText();
		resultImage = '';
		errorOccurred = false;
		if (GetAjaxStatus() != 200)
		{
			document.getElementById(LastIDName).innerHTML = generateErrorString("HTTP request failed with status: " + GetAjaxStatus()); 
			return true;
		}
		if (result.length >= 2 && result.substring(0, 2) == "ok")
		{
			document.getElementById(LastIDName).innerHTML = result.substring(2);
			AbortAjaxRequest(); 
			return true;
		}
		else
		if (result.length >= 5 && result.substring(0, 5) == "error")
		{
			document.getElementById(LastIDName).innerHTML =  generateErrorString(result.substring(5));
			setTimeout('Reconnect('+LastID+')', 5000);
			return true;
		}
		else
		{
			document.getElementById(LastIDName).innerHTML = generateErrorString("Internal Error");
			return true;
		}
	}
	else
		return false;
			
}

function SelectTab(id)
{
	id=prepareTabIndex(id);
	for (var index=1;index<=4;++index) 
	{
		document.getElementById("tab_"+index).className=(id==index)? "selected" : "";
	}
}

function HideContent()
{
	document.getElementById('content').style.visibility="hidden";
}

function ShowContent()
{
	document.getElementById('content').style.visibility="visible";
}

function getCookie(name)
{
	var arg = name + "=";
     var alen = arg.length;
     var clen = document.cookie.length;
     var endstr = 0;
     var i = 0;
     while (i < clen) {
        var j = i + alen;
        if (document.cookie.substring(i, j) == arg){
             endstr = document.cookie.indexOf (";", j);
             if (endstr == -1){
                  endstr = document.cookie.length;
             }
             return unescape(document.cookie.substring(j, endstr));
        }
        i = document.cookie.indexOf(" ", i) + 1;
        if (i == 0) { break; }
      }
      return null;
} 

function prepareTabIndex(tabID)
{
	if(isNaN(tabID)) tabID=1;else
	if (tabID > 4) tabID =4;else
	if (tabID < 1) tabID =1;
	return tabID; 
}

function SelectDefaultTab()
{
	var tabID = getCookie("FILTERS_TAB_INDEX");
	if (tabID == null) {tabID = 1;}
	else {tabID = parseInt(tabID);}
	SelectTab(tabID);Reconnect(tabID);
}

-->
