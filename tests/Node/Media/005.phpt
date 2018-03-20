--TEST--
CommonMark\Node\IMedia URL Errors
--FILE--
<?php
$link = new CommonMark\Node\Link;

try {
	$link->url = [];
} catch(TypeError $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
