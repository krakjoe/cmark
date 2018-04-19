--TEST--
CommonMark\CQL cloning
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
[link](here)
EOD
);

$call = new \CommonMark\CQL(<<<EOD
/children(Paragraph)[/children(Link)]
EOD
);

$cb = function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\Link) {
		echo "OK\n";
	} else  echo "FAIL\n";
};

$call($doc, $cb);

$second = clone $call;

$second($doc, $cb);
?>
--EXPECT--
OK
OK
