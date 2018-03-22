--TEST--
CommonMark\Node\CustomBlock invalid read
--FILE--
<?php
$custom = new CommonMark\Node\CustomBlock;

$zero = 0;

try {
	$custom->$zero;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
