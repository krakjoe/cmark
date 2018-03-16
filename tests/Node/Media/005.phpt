--TEST--
CommonMark\Node\IMedia URL Errors
--FILE--
<?php
$link = new CommonMark\Node\Link;

try {
	$link->setURL([]);
} catch(TypeError $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
