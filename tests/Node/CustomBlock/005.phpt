--TEST--
CommonMark\Node\CustomBlock onLeave Error
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

try {
	$node->onLeave = [];
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
