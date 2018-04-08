--TEST--
CommonMark\CQL constraint BlockQuote
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
  > block quote
  paragraph
EOD
);

$call = new \CommonMark\CQL("/children(BlockQuote)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\BlockQuote) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK

