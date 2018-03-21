--TEST--
CommonMark\Node\Media invalid read
--FILE--
<?php
$link = new CommonMark\Node\Link;

try {
	$link->something;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
