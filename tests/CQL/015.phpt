--TEST--
CommonMark\CQL constraint HTMLBlock
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
<html>
  <head></head>
</html>
EOD
);

$call = new \CommonMark\CQL("/children(HTMLBlock)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\HTMLBlock) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK

