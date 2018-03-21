--TEST--
CommonMark\Node\Media write invalid
--FILE--
<?php
$link = new CommonMark\Node\Link;

try {
	$link->something = "NOT OKAY";
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
