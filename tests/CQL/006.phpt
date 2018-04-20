--TEST--
CommonMark\CQL children
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
Paragraph

Paragraph
EOD
);

$call = new \CommonMark\CQL("/children");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Paragraph) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK
OK

