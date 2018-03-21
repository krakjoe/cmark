--TEST--
CommonMark\Node\Heading incorrect write
--FILE--
<?php
$heading = new CommonMark\Node\Heading();

try {
	$heading->something = "NOT OKAY";
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
