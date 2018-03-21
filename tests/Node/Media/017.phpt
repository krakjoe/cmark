--TEST--
CommonMark\Node\Media unset invalid
--FILE--
<?php
$link = new CommonMark\Node\Link;

$zero = 0;

try {
	unset($link->$zero);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
