--TEST--
CommonMark\CQL constraint Text
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
paragraph with text
EOD
);

$call = new \CommonMark\CQL("/children(Paragraph)[/children(Text)]");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Text) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK

