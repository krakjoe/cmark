--TEST--
CommonMark\Node\CustomInline onLeave Error
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

try {
	$node->onLeave = [];
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
