<?php
	function randCode()
	{
		$key = '';
		$a = 'abcdefghijklmnopqrstuvwxyz';
		$key .= $a[mt_rand(0,25)];
		$i = 0;
		while($i < 4){
			$key .= mt_rand(0,9);
			$i++;
		}
		return $key;
	}
	$now = time();
	if(isset($_POST['t']) && (int)$_POST['t'] - $now <= 10){
		$myfile = fopen("test.txt","r+");
		$codes = '';
		if (flock($myfile,LOCK_EX)){
			while(!feof($myfile)){
				$codes .= fgets($myfile);
			}
			$codeArray = explode(" ",$codes);
			$key = randCode();
			while (array_search($key,$codeArray)){
				$key = randCode();
			}
			fwrite($myfile," ".$key);
			flock($myfile,LOCK_UN);
			echo $key;
		}
		else{
			echo '0';
		}
		fclose($myfile);
	}
	else{
		echo '0';
	}
?>