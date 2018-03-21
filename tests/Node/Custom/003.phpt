--TEST--
CommonMark\Node\Custom incorrect read
--FILE--
<?php
$block = new CommonMark\Node\CustomBlock();

try {
	$block->something;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
