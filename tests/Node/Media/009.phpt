--TEST--
CommonMark\Node\Media invalid read
--FILE--
<?php
$link = new CommonMark\Node\Link;

$zero = 0;

try {
	$link->$zero;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
