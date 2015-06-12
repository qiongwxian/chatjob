var screenWidth;
var screenHeight;
var timing;
var gameTime1,gameTime2,gameTime3;
var temp;
var totScore = 0;
var totTime = 30;
var linkUrl = '';//分享到朋友圈的链接;
var ImgUrl = 'img/logo.png';//链接显示的图片
var timeStamp,nStr,mySignature;

window.onload = function()
{
	document.body.style.opacity = "1";
	showStartPage();
	//alert("\" aaaa \"");
	//getWeixinThing();
	//share();
}

function showStartPage()
{
	screenWidth = window.innerWidth;
	screenHeight = window.innerHeight;
	var startPage = document.getElementById("start_page");
	startPage.style.display = "inline-block";
	startPage.style.height = (screenHeight) + "px";
	var lamp = document.getElementById("lamp_holder");
	lamp.style.width = parseInt(lamp.offsetHeight * 0.75) + "px";
	lamp.setAttribute("class","lamps_holder0");
	document.getElementById("lamp").setAttribute("class","lamps0");
	var socket = document.getElementById("socket");
	socket.style.width = socket.offsetHeight + "px";
	var line = document.getElementById("line");
	line.style.width = socket.offsetHeight + "px";
	line.style.height = parseInt(socket.offsetHeight * 6.72) + "px";
	line.style.left = parseInt(socket.offsetLeft) + "px";
	line.style.top = "100%";
	temp = parseInt((line.offsetTop - (socket.offsetTop + socket.offsetWidth * 0.5)) / 80);
	timing = setTimeout("lineComeUp(temp)",10);
}

function showGamePage()
{
	var gamePage = document.getElementById("game_page");
	document.getElementById("game_page").style.display = "inline-block";
	gamePage.style.height = window.innerHeight + "px";
	for(var i = 1;i <= 3;i++){
		var obj = document.getElementById("game_lamp"+i);
		obj.style.height = parseInt(obj.offsetWidth * 1.45) + "px";
		obj = document.getElementById("game_button"+i);
		obj.style.height = obj.offsetWidth + "px";
	}
	var gameLampBg = document.getElementsByClassName("game_lamp_bg0");
	for(var i = 0;i < gameLampBg.length;i++){
		gameLampBg[i].style.height = parseInt(gameLampBg[i].offsetWidth * 1.45) + "px";
	}
	document.getElementById("score").innerHTML = "0";
	document.getElementById("timeRemain").innerHTML = "00:30";
	//document.getElementById("game_lamp1").setAttribute("class","lamps10");
	totScore = 0;
	totTime = 30;
	gameTime1 = setTimeout("randomLight1()",500);
	gameTime2 = setTimeout("randomLight2()",500);
	gameTime3 = setTimeout("randomLight3()",500);
	timing = setTimeout("timer()",1000);
}

function showResultPage()
{
	var resultPage = document.getElementById("result_page");
	document.getElementById("result_page").style.display = "inline-block";
	resultPage.style.height = window.innerHeight + "px";
	var resultMessage = document.getElementById("result_message");
	resultMessage.style.width = parseInt(resultMessage.offsetHeight * 0.67) + "px";
	var child = resultMessage.childNodes;
	document.getElementById("tot_amount").style.marginTop = parseInt(resultMessage.offsetHeight * 0.12) + "px";
	for(var i = 0;i < child.length;i++){
		var name = child[i].tagName + "";
		if(name.toLowerCase() == 'p'){
			child[i].style.fontSize = parseInt(resultMessage.offsetHeight * 0.05) + "px";
		}
	}
	document.getElementById("honor").style.fontSize = parseInt(resultMessage.offsetHeight * 0.17) + "px";
	document.getElementById("code").style.marginBottom = parseInt(resultMessage.offsetHeight * 0.11) + "px";
	document.getElementById("code").style.fontSize = parseInt(resultMessage.offsetHeight * 0.04) + "px";
	document.getElementById("restart").style.paddingTop = parseInt(resultMessage.offsetHeight * 0.12) + "px";
	var adButton = document.getElementsByClassName("ad_button");
	for(var i = 0;i < adButton.length;i++){
		adButton[i].style.height = adButton[i].offsetWidth + "px";
	}
	document.getElementById("tot_amount").innerHTML = "你电爆了" + totScore + "个灯泡";
	document.getElementById("honor").innerHTML = getHonor();
	getCode();
}

function getHonor()
{
	if(totScore >= 0&&totScore <= 10){
		return '面瘫';
	}
	else if(totScore >= 11&&totScore <= 20){
		return '面糊';
	}
	else if(totScore >= 21&&totScore <= 25){
		return '面渣';
	}
	else if(totScore >= 26&&totScore <= 30){
		return '面霸';
	}
	else if(totScore >= 31&&totScore <= 35){
		return '面圣';
	}
	else if(totScore >= 36){
		return '面神';
	}
	else{
		return '面糊';
	}
}

function lineComeUp(step)
{
	var line = document.getElementById("line");
	var top = line.offsetTop;
	var socketTop = document.getElementById("socket").offsetTop;
	var socketWidth = document.getElementById("socket").offsetWidth;
	if(parseInt(top) <= parseInt(socketTop + socketWidth * 0.5)){
		//alert(parseInt(socketTop + socketWidth * 0.5)+ "  "+top);
		clearTimeout(timing);
		showStartAll()
		return;
	}
	line.style.top = (top - step) + "px";
	timing = setTimeout("lineComeUp(temp)",10);
}

function lineComeUp2(step)
{
	//alert(10);
	var line = document.getElementById("line");
	var top = line.offsetTop;
	var lamp = document.getElementById("lamp_holder");
	if(parseInt(top) <= parseInt(lamp.offsetTop + lamp.offsetHeight - 30)){
		lamp.setAttribute("class","lamps_holder0");
		var num = 0;
		while(parseInt(num) == 0){
			num = Math.random() * 10;
		}
		document.getElementById("lamp").setAttribute("class","lamps" + parseInt(num));
		//alert(num);
		clearTimeout(timing);
		setTimeout('document.getElementById("start_page").style.display = "none";showGamePage();',500);
		return;
	}
	line.style.top = (top - step) + "px";
	timing = setTimeout("lineComeUp2(temp)",10);
}

function showStartAll()
{
	document.getElementsByClassName("message")[0].style.opacity = "1";
	document.getElementsByClassName("gameRules")[0].style.opacity = "1";
	document.getElementsByClassName("rewareRules")[0].style.opacity = "1";
	var num = 0;
	while(parseInt(num) == 0){
		num = Math.random() * 10;
	}
	var lamp = document.getElementById("lamp_holder");
	lamp.setAttribute("class","lamps_holder1");
	document.getElementById("start_page").setAttribute("class","page_light");
	//document.getElementById("lamp").onclick = function(){gameStarting();}
	lamp.onclick = function(){gameStarting();}
}

function gameStarting()
{
	var line = document.getElementById("line");
	var lamp = document.getElementById("lamp_holder");
	temp = parseInt((line.offsetTop - (lamp.offsetTop + lamp.offsetHeight - 30)) / 50);
	if(temp == 0){temp = 1;}
	//alert((line.offsetTop - (lamp.offsetTop + lamp.offsetHeight - 10)) / 50);
	timing = setTimeout("lineComeUp2(temp)",10);
}

function randomLight1()
{
	var p = Math.random();
	var pp = Math.random();
	if(pp < p){
		document.getElementById("game_lamp_bg1").setAttribute("class","game_lamp_bg1");
	}
	else{
		document.getElementById("game_lamp_bg1").setAttribute("class","game_lamp_bg0");
	}
	gameTime1 = setTimeout("randomLight1()",500);
}

function randomLight2()
{
	var p = Math.random();
	var pp = Math.random();
	if(pp < p){
		document.getElementById("game_lamp_bg2").setAttribute("class","game_lamp_bg1");
	}
	else{
		document.getElementById("game_lamp_bg2").setAttribute("class","game_lamp_bg0");
	}
	gameTime2 = setTimeout("randomLight2()",500);
}

function randomLight3()
{
	var p = Math.random();
	var pp = Math.random();
	if(pp < p){
		document.getElementById("game_lamp_bg3").setAttribute("class","game_lamp_bg1");
	}
	else{
		document.getElementById("game_lamp_bg3").setAttribute("class","game_lamp_bg0");
	}
	gameTime3 = setTimeout("randomLight3()",500);
}

function gotOne1()
{
	if(document.getElementById("game_lamp_bg1").className == "game_lamp_bg0"){return;}
	clearTimeout(gameTime1);
	document.getElementById("game_lamp_bg1").setAttribute("class","game_lamp_bg0");
	var lamp = document.getElementById("game_lamp1");
	var num = 0;
	while(parseInt(num) == 0){
		num = Math.random() * 10;
	}
	lamp.setAttribute("class","lamps"+parseInt(num));
	totScore++;
	document.getElementById("score").innerHTML = totScore;
	setTimeout('reset1()',100);
}

function reset1()
{
	document.getElementById("game_lamp1").setAttribute("class","lamps0");
	gameTime1 = setTimeout("randomLight1()",500);
}

function gotOne2()
{
	if(document.getElementById("game_lamp_bg2").className == "game_lamp_bg0"){return;}
	clearTimeout(gameTime2);
	document.getElementById("game_lamp_bg2").setAttribute("class","game_lamp_bg0");
	var lamp = document.getElementById("game_lamp2");
	var num = 0;
	while(parseInt(num) == 0){
		num = Math.random() * 10;
	}
	lamp.setAttribute("class","lamps"+parseInt(num));
	totScore++;
	document.getElementById("score").innerHTML = totScore;
	setTimeout('reset2()',100);
}

function reset2()
{
	document.getElementById("game_lamp2").setAttribute("class","lamps0");
	gameTime1 = setTimeout("randomLight2()",500);
}

function gotOne3()
{
	if(document.getElementById("game_lamp_bg3").className == "game_lamp_bg0"){return;}
	clearTimeout(gameTime3);
	document.getElementById("game_lamp_bg3").setAttribute("class","game_lamp_bg0");
	var lamp = document.getElementById("game_lamp3");
	var num = 0;
	while(parseInt(num) == 0){
		num = Math.random() * 10;
	}
	lamp.setAttribute("class","lamps"+parseInt(num));
	totScore++;
	document.getElementById("score").innerHTML = totScore;
	setTimeout('reset3()',100);
}

function reset3()
{
	document.getElementById("game_lamp3").setAttribute("class","lamps0");
	gameTime1 = setTimeout("randomLight3()",500);
}

function timer()
{
	if(totTime <= 0){
		clearTimeout(timing);
		gameOver();
		return;
	}
	totTime--;
	var minute = parseInt(totTime / 60);
	var sec = totTime % 60;
	if(minute < 10){
		minute = '0' + minute;
	}
	if(sec < 10){
		sec = '0' + sec;
	}
	document.getElementById("timeRemain").innerHTML = minute + ":" + sec;
	timing = setTimeout("timer()",1000);
}

function gameOver()
{
	clearTimeout(gameTime1);
	clearTimeout(gameTime2);
	clearTimeout(gameTime3);
	document.getElementById("game_lamp_bg1").setAttribute("class","game_lamp_bg0");
	document.getElementById("game_lamp1").setAttribute("class","lamps0");
	document.getElementById("game_lamp_bg2").setAttribute("class","game_lamp_bg0");
	document.getElementById("game_lamp2").setAttribute("class","lamps0");
	document.getElementById("game_lamp_bg3").setAttribute("class","game_lamp_bg0");
	document.getElementById("game_lamp3").setAttribute("class","lamps0");
	document.getElementById("game_page").style.display = "none";
	showResultPage();
}

function getCode()
{
	var xmlhttp;
	var t = +new Date();
	var txt,x,i;
	if (window.XMLHttpRequest)
	{// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	}
	else
	{// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
	xmlhttp.onreadystatechange=function()
	{
		if (xmlhttp.readyState==4 && xmlhttp.status==200){
			xmlDoc=xmlhttp.responseText;
			if(xmlDoc != '0'){
				document.getElementById("code").innerHTML = "优惠兑换码:" + xmlDoc;
				//alert(xmlDoc);
			}
		}
	}
	xmlhttp.open("POST","getCode.php",true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("t="+parseInt(t / 1000));
}

function showRestartPage()
{
	var restartPage = document.getElementById("restart_page");
	document.getElementById("restart_page").style.display = "inline-block";
	document.getElementById("result_page").style.display = "none";
	restartPage.style.height = window.innerHeight + "px";
	var restartMessage = document.getElementById("restart_message");
	restartMessage.style.width = parseInt(restartMessage.offsetHeight * 0.67) + "px";
	var child = restartMessage.childNodes;
	for(var i = 0;i < child.length;i++){
		var name = child[i].tagName + "";
		if(name.toLowerCase() == 'p'){
			child[i].style.fontSize = parseInt(restartMessage.offsetHeight * 0.035) + "px";
		}
	}
	document.getElementById("restart_button").style.paddingTop = parseInt(restartMessage.offsetHeight * 0.16) + "px";
	document.getElementById("restart_button").style.fontSize = parseInt(restartMessage.offsetHeight * 0.08) + "px";
	document.getElementById("restart_title").style.fontSize = parseInt(restartMessage.offsetHeight * 0.05) + "px";
}

function randerAboutPage(text)
{
	//var text = '<div class="result_message" id="about_message"><div id="about_title" class="title">CharJob Café</div><br/><p>全国首家大学生求职咖啡社</p><br/><p>区，以“咖啡+”思维的商业模式，</p><br/><p>为大学生打造一站式求职服务咖啡社区。</p><br/><p>我们希望成为</p><br/><p>每一个大学生求职路上</p><br/><p>最喜爱和信赖的伙伴。</p><br/><p id="back_button" onclick="document.getElementById(' + 'about_page' + ').style.display = ' + 'none'+ ';showStartPage();">返回</p></div>'
	var aboutPage = document.getElementById("about_page");
	aboutPage.innerHTML = text;
	document.getElementById("about_page").style.display = "inline-block";
	//document.getElementById("result_page").style.display = "none";
	aboutPage.style.height = window.innerHeight + "px";
	var aboutMessage = document.getElementById("about_message");
	aboutMessage.style.width = parseInt(aboutMessage.offsetHeight * 0.67) + "px";
	var child = aboutMessage.childNodes;
	for(var i = 0;i < child.length;i++){
		var name = child[i].tagName + "";
		if(name.toLowerCase() == 'p'){
			child[i].style.fontSize = parseInt(aboutMessage.offsetHeight * 0.035) + "px";
		}
	}
	document.getElementById("back_button").style.paddingTop = parseInt(aboutMessage.offsetHeight * 0.16) + "px";
	document.getElementById("back_button").style.fontSize = parseInt(aboutMessage.offsetHeight * 0.08) + "px";
	document.getElementById("about_title").style.fontSize = parseInt(aboutMessage.offsetHeight * 0.05) + "px";
}

function showAboutPage()
{
	var text = '<div class="result_message" id="about_message"><div id="about_title" class="title">CharJob Café</div><br/><p>全国首家大学生求职咖啡社</p><br/><p>区，以“咖啡+”思维的商业模式，</p><br/><p>为大学生打造一站式求职服务咖啡社区。</p><br/><p>我们希望成为</p><br/><p>每一个大学生求职路上</p><br/><p>最喜爱和信赖的伙伴。</p><br/><p id="back_button" onclick="document.getElementById(' + "'about_page'" + ').style.display = ' + "'none'"+ ';document.getElementById(\'result_page\').style.display = \'inline-block\';">返回</p></div>'
	randerAboutPage(text);
}

function showRewarePage()
{
	var text = '<div class="result_message" id="about_message"><div id="about_title" class="title">CharJob Café</div><br/><p>优惠：称号"面神""面圣"全单7折</p><br/><p>称号"面霸""面渣"全单8折</p><br/><p>称号"面糊""面瘫"全单9折</p><br/><p>领取方式：</p><br/><p>分享到朋友圈得瑟一下，</p><br/><p>凭兑换码就可以找</p><br/><p>店员领取优惠啦</p><br/><p id="back_button" onclick="document.getElementById('+ "'about_page'" + ').style.display = ' + "'none'" + ';showStartPage();">返回</p></div>'
	randerAboutPage(text);
}

function showRulePage()
{
	var text = '<div class="result_message" id="about_message"><div id="about_title" class="title">CharJob Café</div><br/><p>游戏页面有三个灯泡，</p><br/><p>灯泡点亮时按下灯泡下的按钮</p><br/><p>即可得分。30秒内得分越高可</p><br/><p>获得越多优惠，并可获得</p><br/><p>相应称号，一起来玩吧~</p><br/><p id="back_button" onclick="document.getElementById(' + "'about_page'" + ').style.display = ' + "'none'" + ';showStartPage();">返回</p></div>'
	randerAboutPage(text);
}

function share()
{
	var text = '我的职场电力达到' + totScore + '瓦，不服来战~';
    wx.onMenuShareTimeline({
      title: text,
      link: linkUrl,
      imgUrl: ImgUrl,
      trigger: function (res) {
		  
      },
      success: function (res) {
        //alert('已分享');
      },
      cancel: function (res) {
        //alert('已取消');
      },
      fail: function (res) {
        alert(JSON.stringify(res));
      }
    });
	alert('点击右上角即可分享');
}











