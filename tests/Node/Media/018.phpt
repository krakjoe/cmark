--TEST--
CommonMark\Node\Media unset invalid
--FILE--
<?php
$link = new CommonMark\Node\Link;

try {
	unset($link->something);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
