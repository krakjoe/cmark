--TEST--
CommonMark\Node\IMedia Title Errors
--FILE--
<?php
$link = new CommonMark\Node\Link;

try {
	$link->title = [];
} catch(TypeError $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
