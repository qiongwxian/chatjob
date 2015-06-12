<?php
require_once "jssdk.php";
$jssdk = new JSSDK("wx86ba1a40612ced7a", "70f6a6f8d961181bdc218fb9d2c5c98b");
$signPackage = $jssdk->GetSignPackage();
?>
<!DOCTYPE html> 
<head>
	<meta charset="UTF-8">
	<title>触电</title>
	<meta name="apple-mobile-web-app-capable" content="yes" />
	<meta name="apple-mobile-web-app-status-bar-style" content="black" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1, user-scalable=no, minimal-ui">
	<link href="main.css" rel="stylesheet" type="text/css">
</head>
<body>
	<!--
	<div id="all">
		<canvas id="game" width="60" height="70"></canvas>
	</div>
	-->
	<div class="page_black" id="start_page">
		<div class="title">CharJob Café</div>
		<div class="message">点击灯泡开始游戏</div>
		<div class="lamps_holder0" id="lamp_holder">
			<div class="lamps0" id="lamp"></div>
		</div><br/>
		<div class="gameRules" onclick="document.getElementById('start_page').style.display = 'none';showRulePage();">游戏规则</div>
		<div class="socket" id="socket"></div>
		<div class="rewareRules" onclick="document.getElementById('start_page').style.display = 'none';showRewarePage();">奖励规则</div>
		<div class="line" id="line"></div>
	</div>
	<div class="page_light" id="game_page" style="display: none;">
		<div id="timeRemain">00:30</div>
		<div id="score">0</div>
		<div id="lamp_position1">
			<div class="game_lamp_bg0" id="game_lamp_bg1"></div>
			<div class="lamps0" id="game_lamp1"></div>
			<div id="game_button1" onclick="gotOne1();"></div>
		</div>
		<div id="lamp_position2">
			<div class="game_lamp_bg0" id="game_lamp_bg2"></div>
			<div class="lamps0" id="game_lamp2"></div>
			<div id="game_button2" onclick="gotOne2();"></div>
		</div>
		<div id="lamp_position3">
			<div class="game_lamp_bg0" id="game_lamp_bg3"></div>
			<div class="lamps0" id="game_lamp3"></div>
			<div id="game_button3" onclick="gotOne3();"></div>
		</div>
		<div class="footer">
			<img src="img/logo.png" />
			<div>CharJob Café</div>
		</div>
	</div>
	<div class="page_light" id="result_page" style="display: none;">
		<div class="title">CharJob Café</div>
		<div class="result_message" id="result_message">
			<p id="tot_amount" style="margin-top:"></p><br/>
			<p>获得称号</p><br/>
			<p id="honor"></p><br/>
			<p id="code"></p><br/>
			<p id="restart" onclick="showRestartPage();">再来一次</p>
		</div><br/>
		<div class="ad_button" id="follow" onclick="alert('搜索微信号ChatJob520即可关注我们~')"></div>
		<div class="ad_button" id="about" onclick="document.getElementById('result_page').style.display = 'none';showAboutPage();"></div>
		<div class="ad_button" id="showoff" onclick="share();"></div>
	</div>
	<div class="page_black" id="restart_page" style="display: none;">
		<div class="result_message" id="restart_message">
			<div id="restart_title" class="title">CharJob Café</div><br/>
			<p>全国首家大学生求职咖啡社</p><br/>
			<p>区，以“咖啡+”思维的商业模式，</p><br/>
			<p>为大学生打造一站式求职服务咖啡社区。</p><br/>
			<p>我们希望成为</p><br/>
			<p>每一个大学生求职路上</p><br/>
			<p>最喜爱和信赖的伙伴。</p><br/>
			<p id="restart_button" onclick="document.getElementById('restart_page').style.display = 'none';showGamePage();">开始</p>
		</div>
	</div>
	<div class="page_black" id="about_page" style="display: none;">
		<!--
		<div class="result_message" id="about_message">
			<div id="about_title" class="title">CharJob Café</div><br/>
			<p>全国首家大学生求职咖啡社</p><br/>
			<p>区，以“咖啡+”思维的商业模式，</p><br/>
			<p>为大学生打造一站式求职服务咖啡社区。</p><br/>
			<p>我们希望成为</p><br/>
			<p>每一个大学生求职路上</p><br/>
			<p>最喜爱和信赖的伙伴。</p><br/>
			<p id="back_button" onclick="document.getElementById('about_page').style.display = 'none';showStartPage();">返回</p>
		</div>
		-->
		<div class="result_message" id="about_message">
			<div id="about_title" class="title">CharJob Café</div><br/>
			<p>游戏页面有三个灯泡，</p><br/>
			<p>灯泡点亮时按下灯泡下的按钮</p><br/>
			<p>即可得分。30秒内得分越高可</p><br/>
			<p>获得越多优惠，并可获得</p><br/>
			<p>相应称号，一起来玩吧~</p><br/>
			<p id="back_button" onclick="document.getElementById('about_page').style.display = 'none';showStartPage();">返回</p>
		</div>
	</div>
	<img src="img/black_bg.jpg" style="display: none" />
	<img src="img/light_bg.jpg" style="display: none" />
	<img src="img/buttons.png" style="display: none" />
	<img src="img/lamps1.png" style="display: none" />
	<img src="img/light.png" style="display: none" />
	<img src="img/line.png" style="display: none" />
	<img src="img/resultButton.png" style="display: none" />
	<img src="img/socket.png" style="display: none" />
	<script src="jweixin-1.0.0.js"></script>
	<script>
	  wx.config({
		debug: false,
		appId: '<?php echo $signPackage["appId"];?>',
		timestamp: <?php echo $signPackage["timestamp"];?>,
		nonceStr: '<?php echo $signPackage["nonceStr"];?>',
		signature: '<?php echo $signPackage["signature"];?>',
		jsApiList: [
			'checkJsApi',
			'onMenuShareTimeline',
			'onMenuShareAppMessage',
			'onMenuShareQQ',
			'onMenuShareWeibo',
			'hideMenuItems',
			'showMenuItems',
			'hideAllNonBaseMenuItem',
			'showAllNonBaseMenuItem',
			'translateVoice',
			'startRecord',
			'stopRecord',
			'onRecordEnd',
			'playVoice',
			'pauseVoice',
			'stopVoice',
			'uploadVoice',
			'downloadVoice',
			'chooseImage',
			'previewImage',
			'uploadImage',
			'downloadImage',
			'getNetworkType',
			'openLocation',
			'getLocation',
			'hideOptionMenu',
			'showOptionMenu',
			'closeWindow',
			'scanQRCode',
			'chooseWXPay',
			'openProductSpecificView',
			'addCard',
			'chooseCard',
			'openCard'
		]
	  });
	</script>
	<script src="main.js"></script>
</body>