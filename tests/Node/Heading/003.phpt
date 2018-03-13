--TEST--
CommonMark\Node\Heading Level Error
--FILE--
<?php
$heading = new CommonMark\Node\Heading;

try {
	$heading->setHeadingLevel([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
